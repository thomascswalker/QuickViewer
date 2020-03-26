#include "framebuffer.h"
#include "rendertask.h"
#include "GLES3/gl3.h"
#include <qopenglfunctions_3_3_core.h>

Framebuffer::Framebuffer(QWidget* parent)
    : QOpenGLWidget(parent)
{
    rendertask = new RenderTask();

    mImage = new QImage(512, 512, QImage::Format_RGB32);
    mImage->fill(Qt::gray);
    mColorbuffer = new QOpenGLTexture(*mImage, QOpenGLTexture::DontGenerateMipMaps);

    xPos = 0;
    yPos = 0;
    mScale = 1.0;
    mExposure = 0;
}

void Framebuffer::initializeGL()
{
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
}

void Framebuffer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    float aspect = (float)w / (float)h;
    glOrtho(-aspect, aspect, -1, 1, -1, 1);
}

void Framebuffer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(xPos, yPos, 1.0f);
    glScalef(mScale, mScale, 1.0f);
}

void Framebuffer::setXPosition(int pos)
{
    if (xPos != pos)
    {
        xPos = pos;
        update();
    }
}

void Framebuffer::setYPosition(int pos)
{
    if (yPos != pos)
    {
        yPos = pos;
        update();
    }
}

void Framebuffer::setScale(qreal scale)
{
    if (mScale != scale)
    {
        mScale *= scale;
        update();
    }
}

void Framebuffer::setExposure(float exposure)
{
    if (mExposure != exposure)
    {
        mExposure = exposure;
        update();
    }
}

void Framebuffer::mousePressEvent(QMouseEvent* event)
{
    lastPos = event->pos();
}

void Framebuffer::mouseMoveEvent(QMouseEvent* event)
{
    int deltaX = event->x() - lastPos.x();
    int deltaY = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXPosition(xPos + (1.5 * deltaX) / mScale);
        setYPosition(yPos + (1.5 * deltaY) / mScale);
    }

    lastPos = event->pos();
}

void Framebuffer::wheelEvent(QWheelEvent* event)
{
    qDebug() << event->delta();
    if (event->delta() >= 0)
    {
        setScale(qreal(1.15));
    }
    else
    {
        setScale(qreal(.85));
    }
    
}

void Framebuffer::paintEvent(QPaintEvent* event)
{
    // Clear out the current buffer


    //QPainter painter(this);

    //if (!painter.isActive())
    //{
    //    painter.begin(this);
    //}

    //painter.setRenderHint(QPainter::Antialiasing);
    //rendertask->RenderFrame(&painter, event, mColorbuffer, QPoint(xPos, yPos), mScale);

    //if (painter.isActive())
    //{
    //    painter.end();
    //}
}

void Framebuffer::SetImage(QImage image)
{
    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);

    QOpenGLContext context;
    context.setFormat(format);
    makeCurrent();

    QOpenGLFunctions_3_3_Core functions;

    QOpenGLShader vertex_shader(QOpenGLShader::Vertex);
    if (!vertex_shader.compileSourceCode(
        "#version 330 core\n"
        "\n"
        "void main ()\n"
        "{\n"
        "  gl_Position = vec4(0.0, 0.0, 0.0, 1.0);\n"
        "}\n"
    )) {
        throw std::runtime_error("vertex shader compilaton failed");
    }

    QOpenGLShader fragment_shader(QOpenGLShader::Fragment);
    if (!fragment_shader.compileSourceCode(
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 colour;\n"
        "\n"
        "void main ()\n"
        "{\n"
        "  colour = vec4(0.0, 0.0, 0.0, 1.0);\n"
        "}\n"
    )) {
        throw std::runtime_error("fragment shader compilaton failed");
    }

    QOpenGLShaderProgram program;
    if (!program.addShader(&vertex_shader))
        throw std::runtime_error("failed to add vertex shader to program");
    if (!program.addShader(&fragment_shader))
        throw std::runtime_error("failed to add fragment shader to program");
    if (!program.link())
        throw std::runtime_error("failed to link failed");
    if (!program.bind())
        throw std::runtime_error("glUseProgram failed");

    mImage = &image;

    /*
    float vertices[] = {
        // position    // texture coords
         1.0f, 1.0f,   1.0f, 1.0f,   // top right
         1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
         0.0f, 0.0f,   0.0f, 0.0f,   // bottom left
         0.0f, 1.0f,   0.0f, 1.0f    // top left 
    };

    GLuint VAO;
    functions.glGenVertexArrays(1, &VAO);

    unsigned int texture;
    functions.glGenTextures(1, &texture);
    functions.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, mImage->width(), mImage->height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, mImage->bits());
    functions.glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    functions.glEnableVertexAttribArray(2);
    functions.glBindTexture(GL_TEXTURE_2D, texture);
    functions.glBindVertexArray(VAO);
    functions.glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    */

    update();
}