#ifndef IMAGEPREVIEW_H
#define IMAGEPREVIEW_H

/*
 * This class can open a file from another thread and display its contents as a texture using QOpenGLPainter or raw GL calls
 * */

/* GL and CL*/
#include <CL/opencl.h>

#include "../../qxopengl/qxopengllib.h"
#include "../../qxfile/qxfilelib.h"
#include "../../qxmath/qxmathlib.h"


class ImagePreviewWorker : public OpenGLWorker
{
    Q_OBJECT
public:
    explicit ImagePreviewWorker(QObject *parent = 0);
    ~ImagePreviewWorker();
    void setSharedWindow(SharedContextWindow * window);

signals:
//    void selectionChanged(Selection rect);
//    void backgroundChanged(Selection rect);
//    void pathChanged(QString str);
    void resultFinished(QString str);
    void selectionAlphaChanged(bool value);
    void selectionBetaChanged(bool value);
    void noiseLowChanged(double value);
    void imageChanged(Image image);
    
public slots:
    void setMode(int value);
    void setThresholdNoiseLow(double value);
    void setThresholdNoiseHigh(double value);
    void setThresholdPostCorrectionLow(double value);
    void setThresholdPostCorrectionHigh(double value);
    void setTsfTexture(int value);
    void setTsfAlpha(int value);
    void setLog(bool value);
    void setCorrection(bool value);
    void setAutoBackgroundCorrection(bool value);
    void setDataMin(double value);
    void setDataMax(double value);
//    void displayImage(DetectorFile & file);
//    void refresh();
    void calculus();

    void metaMouseMoveEvent(int x, int y, int left_button, int mid_button, int right_button, int ctrl_button, int shift_button);
    void metaMousePressEvent(int x, int y, int left_button, int mid_button, int right_button, int ctrl_button, int shift_button);
    void metaMouseReleaseEvent(int x, int y, int left_button, int mid_button, int right_button, int ctrl_button, int shift_button);
//    void keyPressEvent(QKeyEvent ev);
//    void keyReleaseEvent(QKeyEvent *ev);
    void wheelEvent(QWheelEvent* ev);
    void resizeEvent(QResizeEvent * ev);
//    void setFrame(Image image);
    void setFrame(Image image);
    void setSelection(QRect rect);
    void setSelectionAlphaActive(bool value);
    void setSelectionBetaActive(bool value);
    void centerImage();
    void analyzeSingle(Image image);
    void analyzeFolder(ImageFolder folder);
    void analyzeSet(FolderSet set);
    
    void peakHuntSingle(Image image);
    void peakHuntFolder(ImageFolder folder);
    void peakHuntSet(FolderSet set);
    
    void showWeightCenter(bool value);
    
private:
    
    // GPU functions
    void imageCalcuclus(cl_mem data_buf_cl, cl_mem out_buf_cl, Matrix<float> &param, Matrix<size_t> &image_size, Matrix<size_t> &local_ws, int correction, float mean, float deviation, int task);
    
    void imageDisplay(cl_mem data_buf_cl, cl_mem frame_image_cl, cl_mem tsf_image_cl, Matrix<float> &data_limit, Matrix<size_t> &image_size, Matrix<size_t> & local_ws, cl_sampler tsf_sampler, int log);
    
    void copyBufferRect(cl_mem cl_buffer, cl_mem cl_copy, Matrix<size_t> &buffer_size, Matrix<size_t> &buffer_origin, Matrix<size_t> &copy_size, Matrix<size_t> &copy_origin, Matrix<size_t> &local_ws);
    
    float sumGpuArray(cl_mem cl_data, unsigned int read_size, Matrix<size_t> &local_ws);
    
    void selectionCalculus(Selection *area, cl_mem image_data_cl, cl_mem image_pos_weight_x_cl_new, cl_mem image_pos_weight_y_cl_new, Matrix<size_t> &image_size, Matrix<size_t> &local_ws);
    
    // Convenience 
    void refreshDisplay();
    void refreshSelection(Selection *area);
    void refreshBackground(Selection *area);
    
    // GPU buffer management
    void maintainImageTexture(Matrix<size_t> &image_size);
    void clMaintainImageBuffers(Matrix<size_t> &image_size);
    
    // GPU buffers
    cl_mem image_data_raw_cl;
    cl_mem image_data_corrected_cl;
    cl_mem image_data_variance_cl;
    cl_mem image_data_skewness_cl;
    cl_mem image_data_weight_x_cl;
    cl_mem image_data_weight_y_cl;
    cl_mem image_data_generic_cl;
    
    // Misc
//    void copyAndReduce(QRect selection_rect);
    
    QString integrationFrameString(DetectorFile &f, Image &image);
    
    SharedContextWindow * shared_window;

    cl_int err;
    cl_program program;
//    cl_kernel cl_image_preview;
    cl_kernel cl_display_image;
    cl_kernel cl_image_calculus;
    cl_mem image_tex_cl;
    cl_mem source_cl;
    cl_mem tsf_tex_cl;
    cl_mem parameter_cl;
    cl_mem image_intensity_cl;
    cl_mem image_pos_weight_x_cl;
    cl_mem image_pos_weight_y_cl;
    
//    cl_mem image_data_raw_cl;
    
    cl_sampler tsf_sampler;
    cl_sampler image_sampler;

    TransferFunction tsf;
    int rgb_style, alpha_style;

    GLuint image_tex_gl;
    GLuint tsf_tex_gl;
    Matrix<size_t> image_tex_size;
    Matrix<size_t> image_buffer_size;
    
    // Eventually merge the following two objects into a single class, or at least name them appropriately
    DetectorFile frame;
    Image frame_image;

    void initOpenCL();
//    void update(size_t w, size_t h);
    void setParameter(Matrix<float> &data);
    void setTsf(TransferFunction & tsf);
    Matrix<double> getScatteringVector(DetectorFile & f, double x, double y);
    double getScatteringAngle(DetectorFile & f, double x, double y);
    Matrix<float> parameter;
    
    void beginRawGLCalls(QPainter * painter);
    void endRawGLCalls(QPainter * painter);

    // Draw
    void drawImage(QPainter *painter);
    void drawTexelOverlay(QPainter *painter);
    void drawSelection(Selection &area, QPainter *painter, Matrix<float> &color);
    void drawWeightpoint(Selection &area, QPainter *painter, Matrix<float> &color);
    void drawToolTip(QPainter * painter);

    // Vertice buffer objects
    GLuint texel_line_vbo[2];

    // Boolean checks
//    bool isInitialized;
    bool isImageTexInitialized;
    bool isTsfTexInitialized;
    bool isCLInitialized;
    bool isFrameValid;
    bool isWeightCenterActive;
    bool isAutoBackgroundCorrectionActive;

    Matrix<double> texture_view_matrix; // Used to draw main texture
    Matrix<double> translation_matrix;
    Matrix<double> zoom_matrix;
    
    Matrix<double> texel_view_matrix; // Used for texel overlay
    Matrix<double> texel_offset_matrix;

    // Mouse
    QPoint pos;
    QPoint prev_pos;
//    int last_mouse_pos_x;
//    int last_mouse_pos_y;

    // Display
    int isLog;
    int isCorrected;
    int mode;

    // Selection
//    Selection analysis_area;
//    Selection background_area;
    GLuint selections_vbo[5];
    GLuint weightpoints_vbo[5];
    bool isSelectionAlphaActive;
    bool isSelectionBetaActive;
    Matrix<int> getImagePixel(int x, int y);

protected:
    void initialize();
    void render(QPainter *painter);
};

class ImagePreviewWindow : public OpenGLWindow
{
    Q_OBJECT

signals:
    void selectionActiveChanged(bool value);
    
public:
    ImagePreviewWindow();
    ~ImagePreviewWindow();

    void setSharedWindow(SharedContextWindow * window);
    ImagePreviewWorker *getWorker();

    void initializeWorker();

public slots:
    void renderNow();
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

private:
    bool isInitialized;

    SharedContextWindow * shared_window;
    ImagePreviewWorker * gl_worker;
};

#endif // IMAGEPREVIEW_H
