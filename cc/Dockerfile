FROM debian:jessie

RUN apt-get update && apt-get install -y --no-install-recommends \
  && apt-get install build-essential -y \
  && apt-get install cmake g++ libopencv-dev libcairomm-1.0-dev -y \
  && mkdir -p /data

ADD data /data

RUN cd /data/mask_wc && make && cp ./maskwc ../maskwc
RUN cd /data/prepare_image && cmake . && make && cp ./prepareImage ../prepareImage


CMD ["/bin/bash"]
