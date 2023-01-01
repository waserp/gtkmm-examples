
#include "FileReader.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

void CSVStringToVector(std::string p_input, std::vector<float>& p_result)
{
  std::stringstream strm(p_input);
  while (strm.good()) {
    std::string substr;
    getline(strm, substr, ',');
    p_result.push_back(atof(substr.c_str()));
  }
}

void ReadDataFileMeda(std::string p_fname, CPlot& p_plot)
{
  std::ifstream ifs(p_fname.c_str(),std::ios_base::binary);
  if (!ifs.is_open()) {
    std::cout << "could not read file\n";
    return;
  }
  std::vector<float> factors;
  
  std::vector<std::vector<float>> data;
  std::vector<float> xvalues;
  int32_t xch = 0;
  size_t dim = 0;
  float dx = 0.0;
  float xval =0.0;
  bool indata=false;
  for (std::string line; std::getline(ifs, line); ) {
    if (line.find("%%")==0) {
      std::cout << line << "\n";
      if (line.find("Title")!= std::string::npos) {
        std::getline(ifs, line); p_plot.SetTitle(line);
      } else if (line.find("xlabel")!= std::string::npos) {
        std::getline(ifs, line); p_plot.SetXlabel(line);
      } else if (line.find("ylabel")!= std::string::npos) {
        std::getline(ifs, line); p_plot.SetYlabel(line);
      } else if (line.find("Faktoren")!= std::string::npos) {
        std::getline(ifs, line); CSVStringToVector(line,factors);
      } else if (line.find("dx")!= std::string::npos) {
        std::vector<float> dxdim;
        std::getline(ifs, line); CSVStringToVector(line,dxdim);
        if (dxdim.size()!=3) {
          std::cout << "error dx dim parameter expects 3 values!\n";
          return;
        }
        xch = lroundf(dxdim[2]);
        dim = lroundf(dxdim[1]);
        dx = dxdim[0];
        data.resize(dim);
      } else if (line.find("daten")!= std::string::npos) {
        indata=true;
      }
    }
    if (indata) {
      std::cout << line << "\n";
      std::vector<float> onedataline;
      CSVStringToVector(line,onedataline);
      std::cout << "ondatasize " << onedataline.size() << "\n";
      if (onedataline.size()==dim) {
        if (xch==0) {
          xval += dx;
          xvalues.push_back(xval);
          int32_t chan = 0;
          for (auto val : onedataline) {
            if (factors.size()==dim) {
              val = val * factors[chan];
            }
            data[chan].push_back(val);
            chan++;
          }
        } else {
          
        } 
      }
    }
  }

  std::cout << "dim " << dim << "\n";
  ifs.close();
  for (size_t idim=0; idim < dim; idim++) {
    std::cout << "ad plot " << idim << "  " <<xvalues.size() << "  " << data[idim].size() << "\n";
    if ((xvalues.size() == data[idim].size()) && (xvalues.size()!=0)) {
      p_plot.AddPlot(xvalues,data[idim]);
    } else {
      std::cout << "inconsistent Data\n";
    }
  }
  std::cout << "end load\n";
}



void ReadDataFile(std::string p_fname, CPlot& p_plot)
{
  if (p_fname.find(".mda")!=std::string::npos) {
    ReadDataFileMeda(p_fname, p_plot);
  }
}

