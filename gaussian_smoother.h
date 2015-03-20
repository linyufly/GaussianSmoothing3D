// Author: Mingcheng Chen (linyufly@gmail.com)

#ifndef GAUSSIAN_SMOOTHER_H_
#define GAUSSIAN_SMOOTHER_H_

class vtkStructuredPoints;

class GaussianSmoother {
 public:
  static vtkStructuredPoints *smooth(vtkStructuredPoints *scalar_field,
                                     double c, int d);
};

#endif  // GAUSSIAN_SMOOTHER_H_

