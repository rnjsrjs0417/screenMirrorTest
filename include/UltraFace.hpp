#ifndef FACEDETECT_HPP
#define FACEDETECT_HPP

#ifndef PRECOMPILE_HPP
    #include <opencv2/opencv.hpp>
#endif
#include <memory>

#define clip(x, y) (x < 0 ? 0 : (x > y ? y : x))

#define num_featuremap 4
#define hard_nms 1
#define blending_nms 2

typedef struct FaceInfo {
    float x1;
    float y1;
    float x2;
    float y2;
    float score;
    std::vector<cv::Point2f> landmark;
} FaceInfo;

class GBThread;
class UltraFace {
public:
    UltraFace(){}
    UltraFace(std::string net_path, int interval = 5,
              float score_threshold_ = 0.7, int detect_size = 300, float iou_threshold_ = 0.3);
    //android
    UltraFace(int interval, float score_threshold_ = 0.7, float iou_threshold_ = 0.3, int topk_ = -1);

    ~UltraFace();

    enum DetectType{
        Face = 0,
        Landmark
    };

    cv::Rect2f                  GetFirstFace(const cv::Mat &img, int resize);
    std::vector<cv::Point2f>    GetLandMark(const cv::Mat &mat, const cv::Rect2f &face);

    //android
    void                        LoadFace(cv::dnn::Net net);
    void                        LoadLandMark(cv::dnn::Net net);

    //c++
    void                        LoadLandMark(std::string landmark_path);
    void                        Init();
    static void                 DrawLandMark(cv::Mat &frame, const std::vector<cv::Point2f> &landmark);

    void                        SetShareData(const cv::Mat& mat, DetectType detect_type);
    cv::Rect2f                  Get_share_face_();
    std::vector<cv::Point2f>    Get_share_landmark_();

    bool                        IsInterval();
    void                        StartInterval();
    void                        StopInterval();
    bool                        isDetecting() const;

    void                        RunDetect();

private:
    //////////////////////////////////////////////////////////////////////////////////////
    //share landmark - thread
    GBThread                        *detect_;
    int                             interval_;
    double                          end_time_face_;

    int                             detect_size_;
    DetectType                      detect_type_;
    float                           share_reduction_;       //share parameter in thread
    cv::Mat                         share_mat_;             //share parameter in thread
    cv::Rect2f                      share_face_;            //share parameter in thread
    std::vector<cv::Point2f>        share_landmark_;        //share parameter in thread
    ////////////////////////////////////////////////////////////////////////////////////////
    cv::dnn::Net model_;
    cv::dnn::Net landmark_;
    bool is_init_;

    int image_w;
    int image_h;

    int num_anchors;

    int topk;
    float score_threshold;
    float iou_threshold;

    const float center_variance = 0.1;
    const float size_variance = 0.2;
    const std::vector<std::vector<float>> min_boxes = {
            {10.0f,  16.0f,  24.0f},
            {32.0f,  48.0f},
            {64.0f,  96.0f},
            {128.0f, 192.0f, 256.0f}
    };
    const std::vector<float> strides = {
            8.0,
            16.0,
            32.0,
            64.0
    };
    std::vector<std::vector<float>> featuremap_size;
    std::vector<std::vector<float>> shrinkage_size;
    std::vector<int> w_h_list;
    std::vector<std::vector<float>> priors = {};

    void                generateBBox(std::vector<FaceInfo> &bbox_collection, cv::Mat scores, cv::Mat boxes, float score_threshold, int num_anchors);
    void                nms(std::vector<FaceInfo> &input, std::vector<FaceInfo> &output, int type = blending_nms);
    cv::Rect2f          GetBestFace(const std::vector<cv::Rect2f> &vec_face);
    void                CheckFaceArea(const cv::Mat& mat, cv::Rect2f &face);
    int                 Detect(const cv::Mat &img, std::vector<cv::Rect2f> &vec_face);

    cv::Rect2f                  GetFirstFace(const cv::Mat &img);

    void                        ResizeLandmark(std::vector<cv::Point2f> &landmark_bgr, double ratio);
    void                        ResizeRect(cv::Rect2f& face, double ratio);
    double                      ResizeMat(cv::Mat& mat, int size);

    double                      GetRound(double value, int n = 0);
};
#endif // FACEDETECT_HPP
