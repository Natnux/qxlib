#ifndef SHAREDCONTEXT_H
#define SHAREDCONTEXT_H

/* QT */
#include <QOpenGLShaderProgram>

#include "openglwindow.h"


class SharedContextWindow : public OpenGLWindow
{
    Q_OBJECT

public:
    explicit SharedContextWindow();
    ~SharedContextWindow();

    // Shaders
    GLint std_2d_tex_fragpos;
    GLint std_2d_tex_pos;
    GLint std_2d_tex_texture;
    GLint std_2d_tex_transform;
    QOpenGLShaderProgram *std_2d_tex_program;
    
    GLint rect_hl_2d_tex_fragpos;
    GLint rect_hl_2d_tex_pos;
    GLint rect_hl_2d_tex_texture;
    GLint rect_hl_2d_tex_transform;
    GLint rect_hl_2d_tex_bounds;
    GLint rect_hl_2d_tex_pixel_size;
//    GLint rect_hl_2d_tex_center;
    QOpenGLShaderProgram *rect_hl_2d_tex_program;
    
    GLint std_2d_col_color;
    GLint std_2d_col_transform;
    GLint std_2d_col_fragpos;
    QOpenGLShaderProgram *std_2d_col_program;

    GLint std_3d_col_color;
    GLint std_3d_col_transform;
    GLint std_3d_col_fragpos;
    QOpenGLShaderProgram *std_3d_col_program;
    
    GLint unitcell_color;
    GLint unitcell_transform;
    GLint unitcell_fragpos;
    GLint unitcell_lim_low;
    GLint unitcell_lim_high;
    GLint unitcell_u;
    QOpenGLShaderProgram *unitcell_program;

    GLint std_blend_fragpos;
    GLint std_blend_texpos;
    GLint std_blend_tex_a;
    GLint std_blend_tex_b;
    GLint std_blend_method;
    QOpenGLShaderProgram *std_blend_program;

    void initializeWorker();

signals:
    void changedMessageString(QString str);

protected:
    void initialize();

private:
    void setMessageString(QString str);

    GLuint loadShader(GLenum type, const char *source);

    cl_int err;

    OpenGLWorker * gl_worker;
};

#endif
