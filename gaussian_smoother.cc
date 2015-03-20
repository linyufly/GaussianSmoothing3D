// Author: Mingcheng Chen (linyufly@gmail.com)

#include "gaussian_smoother.h"

#include <cmath>

#include <algorithm>

#include <vtkDataArray.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredPoints.h>

namespace {

double square(double value) {
  return value * value;
}

double gaussian(double x, double c) {
  return exp(-square(x) / (2 * square(c)));
}

double norm_3d(double x, double y, double z) {
  return sqrt(square(x) + square(y) + square(z));
}

}

vtkStructuredPoints *GaussianSmoother::smooth(
    vtkStructuredPoints *scalar_field, double c, int d) {
  vtkStructuredPoints *smoothed = vtkStructuredPoints::New();
  smoothed->DeepCopy(scalar_field);

  int dimensions[3];
  double spacing[3];
  scalar_field->GetDimensions(dimensions);
  scalar_field->GetSpacing(spacing);

  int nx = dimensions[0];
  int ny = dimensions[1];
  int nz = dimensions[2];

  for (int x = 0; x < nx; x++) {
    for (int y = 0; y < ny; y++) {
      for (int z = 0; z < nz; z++) {
        double sum_value = 0.0;
        double sum_weight = 0.0;

        for (int px = std::max(x - d, 0);
             px <= std::min(nx - 1, x + d); px++) {
          for (int py = std::max(y - d, 0);
               py <= std::min(ny - 1, y + d); py++) {
            for (int pz = std::max(z - d, 0);
                 pz <= std::min(nz - 1, z + d); pz++) {
              int index = (pz * dimensions[1] + py) * dimensions[0] + px;

              double delta_x = (px - x) * spacing[0];
              double delta_y = (py - y) * spacing[1];
              double delta_z = (pz - z) * spacing[2];

              double weight = gaussian(norm_3d(delta_x, delta_y, delta_z), c);
              double value = scalar_field->GetPointData()
                                         ->GetScalars()
                                         ->GetTuple1(index);

              sum_value += value * weight;
              sum_weight += weight;
            }
          }
        }

        smoothed->GetPointData()->GetScalars()->SetTuple1(
            (z * dimensions[1] + y) * dimensions[0] + x,
            sum_value / sum_weight);
      }
    }
  }

  return smoothed;
}
