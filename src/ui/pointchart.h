/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2011-2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef _FNORDMETRIC_POINTCHART_H
#define _FNORDMETRIC_POINTCHART_H
#include <stdlib.h>
#include <assert.h>
#include "../base/series.h"
#include "axisdefinition.h"
#include "domain.h"
#include "drawable.h"

namespace fnordmetric {
namespace ui {
class Canvas;
class Domain;

/**
 * This draws the series data as points.
 *
 * OPTIONS
 *
 *   point_style = {dot,square}, default: horizontal
 *   point_size = default: 5
 *
 */
class PointChart : public Drawable {
public:
  static double kDefaultPointSize;
  static char kDefaultPointStyle[];

  /**
   * Create a new point chart
   *
   * @param canvas the canvas to draw this chart on. does not transfer ownership
   * @param x_domain the x domain. does not transfer ownership
   * @param y_domain the y domain. does not transfer ownership
   */
  PointChart(
      Canvas* canvas,
      NumericalDomain* x_domain = nullptr,
      NumericalDomain* y_domain = nullptr);

  /**
   * Add a (x: string, y: double) series. This will draw one point for each
   * point in the series.
   *
   * @param series the series to add. does not transfer ownership
   */
  void addSeries(
      Series2D<double, double>* series,
      const std::string& point_style = kDefaultPointStyle,
      double point_size = kDefaultPointSize);

  /**
   * Add a (x: string, y: double, z: double) series. This will draw one point
   * for each point in the series with size Z.
   *
   * @param series the series to add. does not transfer ownership
   */
  void addSeries(
      Series3D<double, double, double>* series,
      const std::string& point_style = kDefaultPointStyle);

  /**
   * Add an axis to the chart. This method should only be called after all
   * series have been added to the chart.
   *
   * The returned pointer is owned by the canvas object and must not be freed
   * by the caller!
   *
   * @param position the position/placement of the axis
   */
   AxisDefinition* addAxis(AxisDefinition::kPosition position);

protected:

  NumericalDomain* getXDomain() const;
  NumericalDomain* getYDomain() const;

  void render(
      RenderTarget* target,
      int width,
      int height,
      std::tuple<int, int, int, int>* padding) const override;

  struct Point {
    double x;
    double y;
    double size;
    std::string type;
    std::string color;
  };

  Canvas* canvas_;
  NumericalDomain* x_domain_;
  NumericalDomain* y_domain_;
  int num_series_;
  std::vector<Point> points_;
  mutable std::unique_ptr<NumericalDomain> x_domain_auto_;
  mutable std::unique_ptr<NumericalDomain> y_domain_auto_;
};

}
}
#endif
