#pragma once

#include <string>
#include <QMetaType>
#include "CapTkEnums.h"
//! Structure to define a point value to check if it is defined in the image or not
struct PointVal
{
  PointVal()
  {
    x = y = z = value = 0;
  }
  PointVal(int _x, int _y, int _z)
  {
    x = _x;
    y = _y;
    z = _z;
  }
  PointVal(int _x, int _y, int _z, int _value)
  {
    x = _x;
    y = _y;
    z = _z;
    value = _value;
  }
  bool isWithinRange(const int* dims)
  {
    if (x >= 0 && x < dims[0] && y >= 0 && y < dims[1] && z >= 0 && z < dims[2])
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  bool isValid()
  {
    if (x >= 0 && y >= 0 && z >= 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  PointVal getInvalidPt()
  {
    return PointVal(-1, -1, -1, -1);
  }
  int x, y, z, value;
};

Q_DECLARE_METATYPE(PointVal);
Q_DECLARE_METATYPE(std::vector< PointVal >);

struct NonNativeApp
{
  std::string name;
  std::string path;

  //! Default Constructor
  NonNativeApp()
  {
    name = "";
    path = "";
  }

  //! Default Constructor with values
  NonNativeApp(const std::string &inputName, const std::string &inputPath) :
    name(inputName), path(inputPath) {};
};

/**
\brief Guess Image Type

\param str String to guess
\return deduced type
*/
inline int guessImageType(const std::string &fileName)
{
  int ImageSubType = CAPTK::ImageModalityType::IMAGE_TYPE_UNDEFINED;
  std::string fileName_wrap = fileName;
  std::transform(fileName_wrap.begin(), fileName_wrap.end(), fileName_wrap.begin(), ::tolower);
  if ((fileName_wrap.find("_t1ce") != std::string::npos) || (fileName_wrap.find("_t1-gad") != std::string::npos) ||
    (fileName_wrap.find("_t1-ce") != std::string::npos) || (fileName_wrap.find("_t1-gd") != std::string::npos) ||
    (fileName_wrap.find("_t1gd") != std::string::npos) || (fileName_wrap.find("t1gd_") != std::string::npos) ||
    (fileName_wrap.find("t1ce") != std::string::npos) || (fileName_wrap.find("t1-gad") != std::string::npos) ||
    (fileName_wrap.find("t1-ce") != std::string::npos) || (fileName_wrap.find("t1-gd") != std::string::npos))
  {
    ImageSubType = CAPTK::ImageModalityType::IMAGE_TYPE_T1CE;
  }
  else if ((fileName_wrap.find("_t1") != std::string::npos) || (fileName_wrap.find("t1_") != std::string::npos))
  {
    ImageSubType = CAPTK::ImageModalityType::IMAGE_TYPE_T1;
  }
  else if ((fileName_wrap.find("_t2") != std::string::npos) || (fileName_wrap.find("t2_") != std::string::npos))
  {
    if ((fileName_wrap.find("flair") != std::string::npos))
    {
      ImageSubType = CAPTK::ImageModalityType::IMAGE_TYPE_T2FLAIR;
    }
    else
    {
      ImageSubType = CAPTK::ImageModalityType::IMAGE_TYPE_T2;
    }
  }
  else if ((fileName_wrap.find("_flair") != std::string::npos) || (fileName_wrap.find("flair_") != std::string::npos) || (fileName_wrap.find(".flair.") != std::string::npos))
  {
    ImageSubType = CAPTK::ImageModalityType::IMAGE_TYPE_T2FLAIR;
  }
  else if ((fileName_wrap.find("_dti") != std::string::npos) || (fileName_wrap.find("dti_") != std::string::npos) ||
    (fileName_wrap.find("_b0") != std::string::npos) || (fileName_wrap.find("b0_") != std::string::npos))
  {
    ImageSubType = CAPTK::ImageModalityType::IMAGE_TYPE_DTI;
  }
  else if ((fileName_wrap.find("_rad") != std::string::npos) || (fileName_wrap.find("rad_") != std::string::npos))
  {
    ImageSubType = CAPTK::ImageModalityType::IMAGE_TYPE_RAD;
  }
  else if ((fileName_wrap.find("_ax") != std::string::npos) || (fileName_wrap.find("ax_") != std::string::npos))
  {
    ImageSubType = CAPTK::ImageModalityType::IMAGE_TYPE_AX;
  }
  else if ((fileName_wrap.find("_fa") != std::string::npos) || (fileName_wrap.find("fa_") != std::string::npos))
  {
    ImageSubType = CAPTK::ImageModalityType::IMAGE_TYPE_FA;
  }
  else if ((fileName_wrap.find("_tr") != std::string::npos) || (fileName_wrap.find("tr_") != std::string::npos))
  {
    ImageSubType = CAPTK::ImageModalityType::IMAGE_TYPE_TR;
  }
  else if ((fileName_wrap.find("ct2pet") != std::string::npos) || (fileName_wrap.find("_ct.") != std::string::npos))
  {
    ImageSubType = CAPTK::ImageModalityType::IMAGE_TYPE_CT;
  }
  else if ((fileName_wrap.find("_pet") != std::string::npos) || (fileName_wrap.find("pet_") != std::string::npos) || (fileName_wrap.find("_pet_") != std::string::npos))
  {
    ImageSubType = CAPTK::ImageModalityType::IMAGE_TYPE_PET;
  }
  return ImageSubType;
}

static const char ImageModalityString[CAPTK::ImageModalityType::IMAGE_TYPE_FEATURES + 1][15] =
{ "DEF", "T1", "T1T1CE", "T1Gd", "T2",
"FLAIR", "DTI_AX", "DTI_FA", "DTI_RAD", "DTI_TR", 
"PERFUSION", "DTI", "REC", "PP", "CT", 
"PET", "pSR", "PH", "RCBV", "SEG", 
"ATLAS", "PARAMS", "SUDOID", "NEAR", "FAR", 
"FFDM", "FEAT" };