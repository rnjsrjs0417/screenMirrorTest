#ifndef GB_HEALTH_HPP
#define GB_HEALTH_HPP

#include "lib_header.hpp"

#define IS_LANDMARK

struct BioArgument
{
    cv::Mat mat_bgr;
    cv::Mat mat_ir;
    cv::Rect2f face_bgr;
    cv::Rect2f face_ir;
    std::vector<cv::Point2f> landmark_bgr;
    std::vector<cv::Point2f> landmark_ir;
};


class IrLandmark;
class BgrLandmark;
class BgrFace;

class GBHealth
{
    private:
    #ifdef IS_LANDMARK
    std::shared_ptr<BgrLandmark> pImpl_;
    #else
    std::shared_ptr<BgrFace> pImpl_;
    #endif
    bool pImpl_start_;

    std::shared_ptr<IrLandmark> pImpl_ir_;
    bool pImpl_ir_start_;

    public:
        enum CND {
            CONDITION_WORST = 1,
            CONDITION_BAD,
            CONDITION_LITTLE_BAD,
            CONDITION_GOOD,
        };
        enum ERR {
            FaceNotFound = -1,
            FaceMoving = -2,
            FaceSmall = -3,
            FaceNotCenter = -4
        };

        float           fps_;

        int             bpm_;
        int             blood_pressure_systolic_;
        int             blood_pressure_diastolic_;
        int             spo2_;
        double          temperature_;

        int             condition_;

        GBHealth();
        ~GBHealth();

        // smart mirror - bgr (face detect)
        int             Get(cv::Mat &mat, cv::Rect2f &face);
        int             Get(cv::Mat &mat, std::vector<cv::Point2f> &landmark, cv::Rect& face);
        int             GetIr(cv::Mat &mat, std::vector<cv::Point2f> &landmark, cv::Rect& face);
        void            startInterval(int num=0);
        void            StopInterval(int num=-1);

        void            CallErr(int err);

        void            Reset();
        double          ResizeMat(cv::Mat& mat, int size);
        int 		    getMaxLen();
};
#endif
