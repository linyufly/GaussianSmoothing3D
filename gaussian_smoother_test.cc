// Author: Mingcheng Chen (linyufly@gmail.com)

#include "gaussian_smoother.h"

#include <algorithm>

#include <vtkSmartPointer.h>
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsReader.h>
#include <vtkStructuredPointsWriter.h>

namespace {

// Input files.
const char *kScalarFieldFile = "/home/linyufly/Data/P96_bFTLE.vtk";

// Output files.
const char *kSmoothedFieldFile = "gaussian_smoothed.vtk";

}

void smooth_test() {
  printf("smooth_test {\n");

  vtkSmartPointer<vtkStructuredPointsReader> reader =
      vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(kScalarFieldFile);
  reader->Update();

  vtkSmartPointer<vtkStructuredPoints> field =
      vtkSmartPointer<vtkStructuredPoints>::New();
  field->DeepCopy(reader->GetOutput());

  double spacing[3];
  field->GetSpacing(spacing);

  printf("spacing: %lf, %lf, %lf\n", spacing[0], spacing[1], spacing[2]);

  double gap = std::max(std::max(spacing[0], spacing[1]), spacing[2]);

  vtkSmartPointer<vtkStructuredPoints> smoothed =
      vtkSmartPointer<vtkStructuredPoints>(GaussianSmoother::smooth(
          field, gap, 2));

  vtkSmartPointer<vtkStructuredPointsWriter> writer =
      vtkSmartPointer<vtkStructuredPointsWriter>::New();
  writer->SetInputData(smoothed);
  writer->SetFileName(kSmoothedFieldFile);
  writer->Write();

  printf("} smooth_test\n");
}

int main() {
  smooth_test();

  return 0;
}

