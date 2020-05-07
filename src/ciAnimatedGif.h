#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace cinder {

using ciAnimatedGifRef = std::shared_ptr<class ciAnimatedGif>;

class ciAnimatedGif {
  public:
    ciAnimatedGif() = delete;
    ciAnimatedGif(ci::DataSourceRef data);
    
    static ciAnimatedGifRef create(ci::DataSourceRef data){ return std::make_shared<ciAnimatedGif>(data); }
    static ciAnimatedGifRef create( const cinder::fs::path &path){ return ciAnimatedGif::create( (cinder::DataSourceRef)cinder::DataSourcePath::create( path )); }
    
    void update();
    void draw(cinder::vec2 loc);
    void play();
    void seek( float pct );

    uint16_t                        canvasWidth, canvasHeight;
    
    const std::vector<ci::Color> getPalette(){ return mColorList; };
    
    ci::gl::TextureRef              getTexture(){ return mCurTex; }
    
  protected:
    
    void parseMetadata(ci::DataSourceRef data);
    void printBit(uint8_t byte);
    
    std::vector<ci::gl::TextureRef> mFrameList;
    std::vector<float>              mFrameTimes;
    
    double                          mNextFrameTime = -1;
    int                             mCurFrame = -1;
    ci::gl::TextureRef              mCurTex = nullptr;
    
    std::string                     mHeader;

    bool                            hasGlobalColorTable = false;
    std::vector<ci::Color>          mColorList;
};

}