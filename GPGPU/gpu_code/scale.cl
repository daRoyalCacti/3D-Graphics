__kernel void scale(__global float *input, __global float *output, __global float *scale)
{
  size_t id = get_global_id(0);
  output[id] = scale[0] * input[id];
}
