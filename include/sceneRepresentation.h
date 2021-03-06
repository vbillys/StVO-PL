/*****************************************************************************
**   Stereo Visual Odometry by combining point and line segment features	**
******************************************************************************
**																			**
**	Copyright(c) 2016, Ruben Gomez-Ojeda, University of Malaga              **
**	Copyright(c) 2016, MAPIR group, University of Malaga					**
**																			**
**  This program is free software: you can redistribute it and/or modify	**
**  it under the terms of the GNU General Public License (version 3) as		**
**	published by the Free Software Foundation.								**
**																			**
**  This program is distributed in the hope that it will be useful, but		**
**	WITHOUT ANY WARRANTY; without even the implied warranty of				**
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the			**
**  GNU General Public License for more details.							**
**																			**
**  You should have received a copy of the GNU General Public License		**
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.	**
**																			**
*****************************************************************************/

#include <iomanip>
using namespace std;

#include <mrpt/opengl.h>
#include <mrpt/gui.h>
#include <mrpt/utils/CConfigFile.h>
#include <mrpt/utils/CConfigFileBase.h>
using namespace mrpt;
using namespace mrpt::gui;
using namespace mrpt::poses;
using namespace mrpt::utils;
using namespace mrpt::math;
using namespace mrpt::opengl;

#include <opencv/cv.h>
using namespace cv;

#include <eigen3/Eigen/Core>
using namespace Eigen;

class sceneRepresentation{

public:

    sceneRepresentation();
    sceneRepresentation(string configFile);
    ~sceneRepresentation();
    void initialize3DScene(Matrix4d x_0);
    void initialize3DSceneLines(Matrix4d x_0);
    void initialize3DSceneImg(Matrix4d x_0);
    void initialize3DSceneGT(Matrix4d x_0);

    void initializeScene(Matrix4d x_0);
    void initializeScene(Matrix4d x_0, Matrix4d x_0gt);

    bool updateScene();
    void plotPointsCovariances();
    void plotLinesCovariances();

    void setText(int frame_, float time_, int nPoints_, int nPointsH_, int nLines_, int nLinesH_);
    void setCov(MatrixXd cov_);
    void setPose(Matrix4d x_);
    void setGT(Matrix4d xgt_);
    void setComparison(Matrix4d xcomp_);
    void setImage(Mat image_);
    void setImage(string image_);
    void setLegend();
    void setHelp();
    void setPoints(CMatrixFloat pData_);
    void setLines(CMatrixFloat lData_);
    void setStereoCalibration(Matrix3d K_, float b_);


    bool waitUntilClose();
    bool isOpen();
    bool getYPR(float &yaw, float &pitch, float &roll);
    bool getPose(Matrix4d &T);

private:

    CMatrixDouble getPoseFormat(Matrix4d T);
    CMatrixDouble33 getCovFormat(MatrixXd cov_);
    CPose3D getPoseXYZ(VectorXd x);

    CDisplayWindow3D*           win;
    COpenGLScenePtr             theScene;
    COpenGLViewportPtr          image, legend, help;
    opengl::CSetOfObjectsPtr    bbObj, bbObj1, srefObj, srefObj1, gtObj, srefObjGT, elliObjL, elliObjP;
    opengl::CEllipsoidPtr       elliObj;
    opengl::CSetOfLinesPtr      lineObj;
    opengl::CPointCloudPtr      pointObj;
    opengl::CFrustumPtr         frustObj, frustObj1;
    opengl::CAxisPtr            axesObj;


    float           sbb, saxis, srad, sref, sline, sfreq, szoom, selli, selev, sazim, sfrust, slinef;
    CVectorDouble   v_aux, v_aux_, v_aux1, v_aux1_, v_auxgt, gt_aux_, v_auxgt_;
    CPose3D         pose, pose_0, pose_gt, pose_ini, ellPose, pose1,  change, frustumL_, frustumR_;
    Matrix4d        x_ini;
    mrptKeyModifier kmods;
    int             key;
    CMatrixDouble33 cov3D;
    bool            hasText, hasCov, hasGT, hasChange, hasImg, hasLines, hasPoints, hasFrustum, hasComparison, hasLegend, hasHelp, hasAxes, hasTraj, isKitti;

    Matrix4d        x, xgt, xcomp;
    MatrixXd        cov, W;
    unsigned int    frame, nPoints, nPointsH, nLines, nLinesH;
    float           time;
    string          img, img_legend, img_help;
    CMatrixFloat    lData, pData;
    CImage          img_mrpt_legend, img_mrpt_image, img_mrpt_help;

    float           b, sigmaP, sigmaL, f, cx, cy, bsigmaL, bsigmaP;

};

