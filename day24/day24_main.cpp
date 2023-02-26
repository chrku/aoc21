#include "common.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

std::int64_t step(std::int64_t w, std::int64_t z_p, std::int64_t a_x,
                  std::int64_t a_y, std::int64_t d_z) {
  std::int64_t z_next = 0;
  if (a_x + z_p % 26 != w) {
    z_next = (z_p / d_z) * 26 + a_y + w;
  } else {
    z_next = (z_p / d_z);
  }
  return z_next;
}

std::int64_t getSolutionMaxHelper(const std::vector<std::int64_t> &a_x,
                                  const std::vector<std::int64_t> &a_y,
                                  const std::vector<std::int64_t> &d_z,
                                  const std::vector<std::int64_t> &cum_prod,
                                  std::size_t index, std::int64_t z_p,
                                  std::int64_t &max) {
  if (index >= 14) {
    return z_p;
  }
  if (z_p >= cum_prod[index]) {
    return -1;
  }

  for (std::int64_t i = 9; i >= 1; --i) {
    auto z_next = step(i, z_p, a_x[index], a_y[index], d_z[index]);
    if (getSolutionMaxHelper(a_x, a_y, d_z, cum_prod, index + 1, z_next, max) ==
        0) {
      max += i * static_cast<std::int64_t>(std::pow(10, 13 - index));
      return 0;
    }
  }

  return -1;
}

std::int64_t getSolutionMinHelper(const std::vector<std::int64_t> &a_x,
                                  const std::vector<std::int64_t> &a_y,
                                  const std::vector<std::int64_t> &d_z,
                                  const std::vector<std::int64_t> &cum_prod,
                                  std::size_t index, std::int64_t z_p,
                                  std::int64_t &max) {
  if (index >= 14) {
    return z_p;
  }
  if (z_p >= cum_prod[index]) {
    return -1;
  }

  for (std::int64_t i = 1; i <= 9; ++i) {
    auto z_next = step(i, z_p, a_x[index], a_y[index], d_z[index]);
    if (getSolutionMinHelper(a_x, a_y, d_z, cum_prod, index + 1, z_next, max) ==
        0) {
      max += i * static_cast<std::int64_t>(std::pow(10, 13 - index));
      return 0;
    }
  }

  return -1;
}

std::int64_t getSolution(const std::vector<std::int64_t> &a_x,
                         const std::vector<std::int64_t> &a_y,
                         const std::vector<std::int64_t> &d_z, bool max) {
  std::vector<std::int64_t> cum_product(14, 1);
  cum_product[0] = d_z[d_z.size() - 1];

  for (std::int64_t i = d_z.size() - 2; i >= 0; --i) {
    cum_product[d_z.size() - 1 - i] = cum_product[d_z.size() - i - 2] * d_z[i];
  }
  std::reverse(cum_product.begin(), cum_product.end());
  std::int64_t val = 0;

  if (max) {
    getSolutionMaxHelper(a_x, a_y, d_z, cum_product, 0, 0, val);
  } else {
    getSolutionMinHelper(a_x, a_y, d_z, cum_product, 0, 0, val);
  }
  return val;
}

int main() {
  std::cout << getSolution(
                   {15, 12, 13, -14, 15, -7, 14, 15, 15, -7, -8, -7, -5, -10},
                   {15, 5, 6, 7, 9, 6, 14, 3, 1, 3, 4, 6, 7, 1},
                   {1, 1, 1, 26, 1, 26, 1, 1, 1, 26, 26, 26, 26, 26}, true)
            << std::endl;
  std::cout << getSolution(
                   {15, 12, 13, -14, 15, -7, 14, 15, 15, -7, -8, -7, -5, -10},
                   {15, 5, 6, 7, 9, 6, 14, 3, 1, 3, 4, 6, 7, 1},
                   {1, 1, 1, 26, 1, 26, 1, 1, 1, 26, 26, 26, 26, 26}, false)
            << std::endl;
  return 0;
}
