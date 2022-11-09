# cv3d-semi_global_matching

## Install

```bash
conda env create -f environment.yml
```

* 修改build.sh中的依赖的软件的路径
  * OpencvInstallPath=your-conda-dir/envs/algo-v1
  * GtestInstallPath: 如果为空的话cmake会自动下载并编译依赖;已下载好的路径为GtestInstallDir/include, GtestInstallDir/lib-static

## How to use

```bash
bash build.sh 1
cd  build
make test 
make check
```
