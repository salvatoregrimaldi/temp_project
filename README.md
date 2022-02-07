# Contest-MPI

## Dependencies

- CMake 3.9+
- MPICH
- Python3.9
- Pipenv

## How to run

Since 2 versions of Counting Sort are provided, you must use command
`cd version1` or `cd version2` in order to choose the version to run and:

1. Create a build directory and launch cmake

   ```batch
   mkdir build
   cd build
   cmake ..
   ```

2. Generate executables with `make`

3. To generate measures, run `make generate_output`

   >  ***Attention***: it takes a lot of time. This is the reason why our measures are already included, so you should skip this step.

4. To extract mean times and speedup curves from them run `make extract_measures`

Results can be found in the `measure/YYYY-MM-DD.hh:mm:ss` directory, divided by problem size and the gcc optimization option used.
