docker build . -t sokol-shdc
docker run --name shdc sokol-shdc
docker cp shdc:/workspace/fips-deploy/sokol-tools/linux-ninja-release/sokol-shdc .
docker rm shdc
docker rmi sokol-shdc
