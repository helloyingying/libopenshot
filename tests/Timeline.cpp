/**
 * @file
 * @brief Unit tests for openshot::Timeline
 * @author Jonathan Thomas <jonathan@openshot.org>
 *
 * @ref License
 */

// Copyright (c) 2008-2019 OpenShot Studios, LLC
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <string>
#include <sstream>
#include <memory>
#include <list>
#include <omp.h>

#include "openshot_catch.h"

#include "Timeline.h"
#include "Clip.h"
#include "Frame.h"
#include "Fraction.h"
#include "effects/Blur.h"
#include "effects/Negate.h"

using namespace openshot;

TEST_CASE( "constructor", "[libopenshot][timeline]" )
{
	Fraction fps(30000,1000);
	Timeline t1(640, 480, fps, 44100, 2, LAYOUT_STEREO);

	// Check values
	CHECK(t1.info.width == 640);
	CHECK(t1.info.height == 480);

	Timeline t2(300, 240, fps, 44100, 2, LAYOUT_STEREO);

	// Check values
	CHECK(t2.info.width == 300);
	CHECK(t2.info.height == 240);
}

TEST_CASE( "Set Json and clear clips", "[libopenshot][timeline]" )
{
    Fraction fps(30000,1000);
    Timeline t(640, 480, fps, 44100, 2, LAYOUT_STEREO);

    // Large ugly JSON project (4 clips + 3 transitions)
    std::stringstream project_json;
    project_json << "{\"id\":\"CQA0YW6I2Q\",\"fps\":{\"num\":30,\"den\":1},\"display_ratio\":{\"num\":16,\"den\":9},\"pixel_ratio\":{\"num\":1,\"den\":1},\"width\":1280,\"height\":720,\"sample_rate\":48000,\"channels\":2,\"channel_layout\":3,\"settings\":{},\"clips\":[{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"anchor\":0,\"channel_filter\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"channel_mapping\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"display\":0,\"duration\":51.9466667175293,\"effects\":[],\"end\":10.666666666666666,\"gravity\":4,\"has_audio\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"has_video\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"id\":\"QHESI4ZW0E\",\"layer\":5000000,\"location_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"location_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"mixing\":0,\"origin_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"origin_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"parentObjectId\":\"\",\"perspective_c1_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c1_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"position\":0,\"reader\":{\"acodec\":\"aac\",\"audio_bit_rate\":126694,\"audio_stream_index\":1,\"audio_timebase\":{\"den\":48000,\"num\":1},\"channel_layout\":3,\"channels\":2,\"display_ratio\":{\"den\":9,\"num\":16},\"duration\":51.9466667175293,\"file_size\":\"7608204\",\"fps\":{\"den\":1,\"num\":24},\"has_audio\":true,\"has_single_image\":false,\"has_video\":true,\"height\":720,\"interlaced_frame\":false,\"metadata\":{\"artist\":\"Durian Open Movie Team\",\"compatible_brands\":\"isomiso2avc1mp41\",\"copyright\":\"(c) copyright Blender Foundation | durian.blender.org\",\"creation_time\":\"1970-01-01T00:00:00.000000Z\",\"description\":\"Trailer for the Sintel open movie project\",\"encoder\":\"Lavf52.62.0\",\"handler_name\":\"SoundHandler\",\"language\":\"und\",\"major_brand\":\"isom\",\"minor_version\":\"512\",\"title\":\"Sintel Trailer\"},\"path\":\"" << TEST_MEDIA_PATH << "sintel_trailer-720p.mp4\",\"pixel_format\":0,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":48000,\"top_field_first\":true,\"type\":\"FFmpegReader\",\"vcodec\":\"h264\",\"video_bit_rate\":145725,\"video_length\":\"1253\",\"video_stream_index\":0,\"video_timebase\":{\"den\":24,\"num\":1},\"width\":1280},\"rotation\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale\":1,\"scale_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"start\":0,\"time\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"volume\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"wave_color\":{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"blue\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"green\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":123},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"red\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]}},\"waveform\":false,\"file_id\":\"XL7T80Y9R1\",\"title\":\"sintel_trailer-720p.mp4\",\"image\":\"@assets/thumbnail/XL7T80Y9R1.png\"},{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"anchor\":0,\"channel_filter\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"channel_mapping\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"display\":0,\"duration\":51.9466667175293,\"effects\":[],\"end\":20.866666666666667,\"gravity\":4,\"has_audio\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"has_video\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"layer\":5000000,\"location_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"location_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"mixing\":0,\"origin_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"origin_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"parentObjectId\":\"\",\"perspective_c1_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c1_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"position\":5.7,\"reader\":{\"acodec\":\"aac\",\"audio_bit_rate\":126694,\"audio_stream_index\":1,\"audio_timebase\":{\"den\":48000,\"num\":1},\"channel_layout\":3,\"channels\":2,\"display_ratio\":{\"den\":9,\"num\":16},\"duration\":51.9466667175293,\"file_size\":\"7608204\",\"fps\":{\"den\":1,\"num\":24},\"has_audio\":true,\"has_single_image\":false,\"has_video\":true,\"height\":720,\"interlaced_frame\":false,\"metadata\":{\"artist\":\"Durian Open Movie Team\",\"compatible_brands\":\"isomiso2avc1mp41\",\"copyright\":\"(c) copyright Blender Foundation | durian.blender.org\",\"creation_time\":\"1970-01-01T00:00:00.000000Z\",\"description\":\"Trailer for the Sintel open movie project\",\"encoder\":\"Lavf52.62.0\",\"handler_name\":\"SoundHandler\",\"language\":\"und\",\"major_brand\":\"isom\",\"minor_version\":\"512\",\"title\":\"Sintel Trailer\"},\"path\":\"" << TEST_MEDIA_PATH << "sintel_trailer-720p.mp4\",\"pixel_format\":0,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":48000,\"top_field_first\":true,\"type\":\"FFmpegReader\",\"vcodec\":\"h264\",\"video_bit_rate\":145725,\"video_length\":\"1253\",\"video_stream_index\":0,\"video_timebase\":{\"den\":24,\"num\":1},\"width\":1280},\"rotation\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale\":1,\"scale_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"start\":10.666666666666666,\"time\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"volume\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"wave_color\":{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"blue\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"green\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":123},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"red\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]}},\"waveform\":false,\"file_id\":\"XL7T80Y9R1\",\"title\":\"sintel_trailer-720p.mp4\",\"id\":\"KQK39ZFGJE\",\"image\":\"@assets/thumbnail/XL7T80Y9R1.png\"},{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"anchor\":0,\"channel_filter\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"channel_mapping\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"display\":0,\"duration\":51.9466667175293,\"effects\":[],\"end\":29.566666666666666,\"gravity\":4,\"has_audio\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"has_video\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"layer\":5000000,\"location_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"location_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"mixing\":0,\"origin_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"origin_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"parentObjectId\":\"\",\"perspective_c1_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c1_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"position\":12.3,\"reader\":{\"acodec\":\"aac\",\"audio_bit_rate\":126694,\"audio_stream_index\":1,\"audio_timebase\":{\"den\":48000,\"num\":1},\"channel_layout\":3,\"channels\":2,\"display_ratio\":{\"den\":9,\"num\":16},\"duration\":51.9466667175293,\"file_size\":\"7608204\",\"fps\":{\"den\":1,\"num\":24},\"has_audio\":true,\"has_single_image\":false,\"has_video\":true,\"height\":720,\"interlaced_frame\":false,\"metadata\":{\"artist\":\"Durian Open Movie Team\",\"compatible_brands\":\"isomiso2avc1mp41\",\"copyright\":\"(c) copyright Blender Foundation | durian.blender.org\",\"creation_time\":\"1970-01-01T00:00:00.000000Z\",\"description\":\"Trailer for the Sintel open movie project\",\"encoder\":\"Lavf52.62.0\",\"handler_name\":\"SoundHandler\",\"language\":\"und\",\"major_brand\":\"isom\",\"minor_version\":\"512\",\"title\":\"Sintel Trailer\"},\"path\":\"" << TEST_MEDIA_PATH << "sintel_trailer-720p.mp4\",\"pixel_format\":0,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":48000,\"top_field_first\":true,\"type\":\"FFmpegReader\",\"vcodec\":\"h264\",\"video_bit_rate\":145725,\"video_length\":\"1253\",\"video_stream_index\":0,\"video_timebase\":{\"den\":24,\"num\":1},\"width\":1280},\"rotation\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale\":1,\"scale_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"start\":20.866666666666667,\"time\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"volume\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"wave_color\":{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"blue\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"green\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":123},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"red\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]}},\"waveform\":false,\"file_id\":\"XL7T80Y9R1\",\"title\":\"sintel_trailer-720p.mp4\",\"id\":\"TMKI8CK7QQ\",\"image\":\"@assets/thumbnail/XL7T80Y9R1.png\"},{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0},{\"co\":{\"X\":91,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0},{\"co\":{\"X\":541,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0},{\"co\":{\"X\":631,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"anchor\":0,\"channel_filter\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"channel_mapping\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"display\":0,\"duration\":3600,\"effects\":[],\"end\":21,\"gravity\":4,\"has_audio\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"has_video\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"id\":\"2CQVCHPATF\",\"layer\":6000000,\"location_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"location_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"mixing\":0,\"origin_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"origin_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"parentObjectId\":\"\",\"perspective_c1_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c1_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"position\":0,\"reader\":{\"acodec\":\"\",\"audio_bit_rate\":0,\"audio_stream_index\":-1,\"audio_timebase\":{\"den\":1,\"num\":1},\"channel_layout\":4,\"channels\":0,\"display_ratio\":{\"den\":2,\"num\":3},\"duration\":3600,\"file_size\":\"1382400\",\"fps\":{\"den\":1,\"num\":30},\"has_audio\":false,\"has_single_image\":true,\"has_video\":true,\"height\":480,\"interlaced_frame\":false,\"metadata\":{},\"path\":\"" << TEST_MEDIA_PATH << "front3.png\",\"pixel_format\":-1,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":0,\"top_field_first\":true,\"type\":\"QtImageReader\",\"vcodec\":\"\",\"video_bit_rate\":0,\"video_length\":\"108000\",\"video_stream_index\":-1,\"video_timebase\":{\"den\":30,\"num\":1},\"width\":720},\"rotation\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale\":1,\"scale_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"start\":0,\"time\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"volume\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"wave_color\":{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"blue\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"green\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":123},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"red\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]}},\"waveform\":false,\"file_id\":\"RY3OYWU7HK\",\"title\":\"front3.png\",\"image\":\"@assets/thumbnail/RY3OYWU7HK.png\"}],\"effects\":[{\"id\":\"335XHEZJNX\",\"layer\":5000000,\"title\":\"Transition\",\"type\":\"Mask\",\"position\":5.7,\"start\":0,\"end\":4.966666666666666,\"brightness\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0},{\"co\":{\"X\":150,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"contrast\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":3},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"reader\":{\"acodec\":\"\",\"audio_bit_rate\":0,\"audio_stream_index\":-1,\"audio_timebase\":{\"den\":1,\"num\":1},\"channel_layout\":4,\"channels\":0,\"display_ratio\":{\"den\":4,\"num\":5},\"duration\":3600,\"file_size\":\"5832000\",\"fps\":{\"den\":1,\"num\":30},\"has_audio\":false,\"has_single_image\":true,\"has_video\":true,\"height\":576,\"interlaced_frame\":false,\"metadata\":{},\"path\":\"" << TEST_MEDIA_PATH << "mask.png\",\"pixel_format\":-1,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":0,\"top_field_first\":true,\"type\":\"QtImageReader\",\"vcodec\":\"\",\"video_bit_rate\":0,\"video_length\":\"108000\",\"video_stream_index\":-1,\"video_timebase\":{\"den\":30,\"num\":1},\"width\":720},\"replace_image\":false},{\"id\":\"QQECKBIYUP\",\"layer\":5000000,\"title\":\"Transition\",\"type\":\"Mask\",\"position\":12.3,\"start\":0,\"end\":3.6000000000000014,\"brightness\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0},{\"co\":{\"X\":109,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"contrast\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":3},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"reader\":{\"acodec\":\"\",\"audio_bit_rate\":0,\"audio_stream_index\":-1,\"audio_timebase\":{\"den\":1,\"num\":1},\"channel_layout\":4,\"channels\":0,\"display_ratio\":{\"den\":4,\"num\":5},\"duration\":3600,\"file_size\":\"5832000\",\"fps\":{\"den\":1,\"num\":30},\"has_audio\":false,\"has_single_image\":true,\"has_video\":true,\"height\":576,\"interlaced_frame\":false,\"metadata\":{},\"path\":\"" << TEST_MEDIA_PATH << "mask.png\",\"pixel_format\":-1,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":0,\"top_field_first\":true,\"type\":\"QtImageReader\",\"vcodec\":\"\",\"video_bit_rate\":0,\"video_length\":\"108000\",\"video_stream_index\":-1,\"video_timebase\":{\"den\":30,\"num\":1},\"width\":720},\"replace_image\":false},{\"id\":\"YELU1J5KI8\",\"layer\":5000000,\"title\":\"Transition\",\"type\":\"Mask\",\"position\":17.7,\"start\":0,\"end\":3.3000000000000007,\"brightness\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0},{\"co\":{\"X\":100,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"contrast\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":3},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"reader\":{\"acodec\":\"\",\"audio_bit_rate\":0,\"audio_stream_index\":-1,\"audio_timebase\":{\"den\":1,\"num\":1},\"channel_layout\":4,\"channels\":0,\"display_ratio\":{\"den\":4,\"num\":5},\"duration\":3600,\"file_size\":\"5832000\",\"fps\":{\"den\":1,\"num\":30},\"has_audio\":false,\"has_single_image\":true,\"has_video\":true,\"height\":576,\"interlaced_frame\":false,\"metadata\":{},\"path\":\"" << TEST_MEDIA_PATH << "mask.png\",\"pixel_format\":-1,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":0,\"top_field_first\":true,\"type\":\"QtImageReader\",\"vcodec\":\"\",\"video_bit_rate\":0,\"video_length\":\"108000\",\"video_stream_index\":-1,\"video_timebase\":{\"den\":30,\"num\":1},\"width\":720},\"replace_image\":false}],\"duration\":300,\"scale\":15,\"tick_pixels\":100,\"playhead_position\":0,\"profile\":\"HD 720p 30 fps\",\"layers\":[{\"id\":\"L1\",\"label\":\"\",\"number\":1000000,\"y\":0,\"lock\":false},{\"id\":\"L2\",\"label\":\"\",\"number\":2000000,\"y\":0,\"lock\":false},{\"id\":\"L3\",\"label\":\"\",\"number\":3000000,\"y\":0,\"lock\":false},{\"id\":\"L4\",\"label\":\"\",\"number\":4000000,\"y\":0,\"lock\":false},{\"id\":\"L5\",\"label\":\"\",\"number\":5000000,\"y\":0,\"lock\":false},{\"number\":6000000,\"y\":0,\"label\":\"\",\"lock\":false,\"id\":\"4U4NB9QVD2\"}],\"markers\":[],\"progress\":[],\"version\":{\"openshot-qt\":\"2.6.1-dev\",\"libopenshot\":\"0.2.7-dev\"}}";
    t.SetJson(project_json.str());

    // Count clips & effects
    CHECK(t.Clips().size() == 4);
    CHECK(t.Effects().size() == 3);

    // Clear timeline and clear allocated clips, effects, and frame mappers
    t.Clear();

    // Count clips & effects
    CHECK(t.Clips().size() == 0);
    CHECK(t.Effects().size() == 0);

    // Manually add clip object (not using SetJson)
    std::stringstream path;
    path << TEST_MEDIA_PATH << "test.mp4";
    Clip clip_video(path.str());
    t.AddClip(&clip_video);

    // Manually add effect object (not using SetJson)
    Negate effect_top;
    effect_top.Id("C");
    t.AddEffect(&effect_top);

    // Count clips & effects
    CHECK(t.Clips().size() == 1);
    CHECK(t.Effects().size() == 1);

    // Clear timeline
    t.Clear();

    // Count clips & effects
    CHECK(t.Clips().size() == 0);
    CHECK(t.Effects().size() == 0);
}

TEST_CASE("ReaderInfo constructor", "[libopenshot][timeline]")
{
	// Create a reader
	std::stringstream path;
	path << TEST_MEDIA_PATH << "test.mp4";
	Clip clip_video(path.str());
	clip_video.Open();
	const auto r1 = clip_video.Reader();

	// Configure a Timeline with the same parameters
	Timeline t1(r1->info);

	CHECK(r1->info.width == t1.info.width);
	CHECK(r1->info.height == t1.info.height);
	CHECK(r1->info.fps.num == t1.info.fps.num);
	CHECK(r1->info.fps.den == t1.info.fps.den);
	CHECK(r1->info.sample_rate == t1.info.sample_rate);
	CHECK(r1->info.channels == t1.info.channels);
	CHECK(r1->info.channel_layout == t1.info.channel_layout);
}

TEST_CASE( "width and height functions", "[libopenshot][timeline]" )
{
	Fraction fps(30000,1000);
	Timeline t1(640, 480, fps, 44100, 2, LAYOUT_STEREO);

	// Check values
	CHECK(t1.info.width == 640);
	CHECK(t1.info.height == 480);

	// Set width
	t1.info.width = 600;

	// Check values
	CHECK(t1.info.width == 600);
	CHECK(t1.info.height == 480);

	// Set height
	t1.info.height = 400;

	// Check values
	CHECK(t1.info.width == 600);
	CHECK(t1.info.height == 400);
}

TEST_CASE( "Framerate", "[libopenshot][timeline]" )
{
	Fraction fps(24,1);
	Timeline t1(640, 480, fps, 44100, 2, LAYOUT_STEREO);

	// Check values
	CHECK(t1.info.fps.ToFloat() == Approx(24.0f).margin(0.00001));
}

TEST_CASE( "two-track video", "[libopenshot][timeline]" )
{
	// Create a reader
	std::stringstream path;
	path << TEST_MEDIA_PATH << "test.mp4";
	Clip clip_video(path.str());
	clip_video.Layer(0);
	clip_video.Position(0.0);

	std::stringstream path_overlay;
	path_overlay << TEST_MEDIA_PATH << "front3.png";
	Clip clip_overlay(path_overlay.str());
	clip_overlay.Layer(1);
	clip_overlay.Position(0.05); // Delay the overlay by 0.05 seconds
	clip_overlay.End(0.5);	// Make the duration of the overlay 1/2 second

	// Create a timeline
	Timeline t(1280, 720, Fraction(30, 1), 44100, 2, LAYOUT_STEREO);

	// Add clips
	t.AddClip(&clip_video);
	t.AddClip(&clip_overlay);

	t.Open();

	std::shared_ptr<Frame> f = t.GetFrame(1);

	// Get the image data
	int pixel_row = 200;
	int pixel_index = 230 * 4; // pixel 230 (4 bytes per pixel)

	// Check image properties
	CHECK((int)f->GetPixels(pixel_row)[pixel_index] == Approx(21).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 1] == Approx(191).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 2] == Approx(0).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 3] == Approx(255).margin(5));

	f = t.GetFrame(2);

	// Check image properties
	CHECK((int)f->GetPixels(pixel_row)[pixel_index] == Approx(176).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 1] == Approx(0).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 2] == Approx(186).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 3] == Approx(255).margin(5));

	f = t.GetFrame(3);

	// Check image properties
	CHECK((int)f->GetPixels(pixel_row)[pixel_index] == Approx(23).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 1] == Approx(190).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 2] == Approx(0).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 3] == Approx(255).margin(5));

	f = t.GetFrame(24);

	// Check image properties
	CHECK((int)f->GetPixels(pixel_row)[pixel_index] == Approx(176).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 1] == Approx(0).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 2] == Approx(186).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 3] == Approx(255).margin(5));

	f = t.GetFrame(5);

	// Check image properties
	CHECK((int)f->GetPixels(pixel_row)[pixel_index] == Approx(23).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 1] == Approx(190).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 2] == Approx(0).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 3] == Approx(255).margin(5));

	f = t.GetFrame(25);

	// Check image properties
	CHECK((int)f->GetPixels(pixel_row)[pixel_index] == Approx(20).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 1] == Approx(190).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 2] == Approx(0).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 3] == Approx(255).margin(5));

	f = t.GetFrame(4);

	// Check image properties
	CHECK((int)f->GetPixels(pixel_row)[pixel_index] == Approx(176).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 1] == Approx(0).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 2] == Approx(186).margin(5));
	CHECK((int)f->GetPixels(pixel_row)[pixel_index + 3] == Approx(255).margin(5));

	t.Close();
}

TEST_CASE( "Clip order", "[libopenshot][timeline]" )
{
	// Create a timeline
	Timeline t(640, 480, Fraction(30, 1), 44100, 2, LAYOUT_STEREO);

	// Add some clips out of order
	std::stringstream path_top;
	path_top << TEST_MEDIA_PATH << "front3.png";
	Clip clip_top(path_top.str());
	clip_top.Layer(2);
	t.AddClip(&clip_top);

	std::stringstream path_middle;
	path_middle << TEST_MEDIA_PATH << "front.png";
	Clip clip_middle(path_middle.str());
	clip_middle.Layer(0);
	t.AddClip(&clip_middle);

	std::stringstream path_bottom;
	path_bottom << TEST_MEDIA_PATH << "back.png";
	Clip clip_bottom(path_bottom.str());
	clip_bottom.Layer(1);
	t.AddClip(&clip_bottom);

	t.Open();

	// Loop through Clips and check order (they should have been sorted into the correct order)
	// Bottom layer to top layer, then by position.
	std::list<Clip*> clips = t.Clips();
	int n = 0;
	for (auto clip : clips) {
		CHECK(clip->Layer() == n);
		++n;
	}

	// Add another clip
	std::stringstream path_middle1;
	path_middle1 << TEST_MEDIA_PATH << "interlaced.png";
	Clip clip_middle1(path_middle1.str());
	clip_middle1.Layer(1);
	clip_middle1.Position(0.5);
	t.AddClip(&clip_middle1);

	// Loop through clips again, and re-check order
	clips = t.Clips();
	n = 0;
	for (auto clip : clips) {
		switch (n) {
		case 0:
			CHECK(clip->Layer() == 0);
			break;
		case 1:
			CHECK(clip->Layer() == 1);
			CHECK(clip->Position() == Approx(0.0).margin(0.0001));
			break;
		case 2:
			CHECK(clip->Layer() == 1);
			CHECK(clip->Position() == Approx(0.5).margin(0.0001));
			break;
		case 3:
			CHECK(clip->Layer() == 2);
			break;
		}
		++n;
	}

	t.Close();
}

TEST_CASE( "TimelineBase", "[libopenshot][timeline]" )
{
    // Create a timeline
    Timeline t(640, 480, Fraction(30, 1), 44100, 2, LAYOUT_STEREO);

    // Add some clips out of order
    std::stringstream path;
    path << TEST_MEDIA_PATH << "front3.png";
    Clip clip1(path.str());
    clip1.Layer(1);
    t.AddClip(&clip1);

    Clip clip2(path.str());
    clip2.Layer(0);
    t.AddClip(&clip2);

    // Verify that the list of clips can be accessed
    // through the Clips() method of a TimelineBase*
    TimelineBase* base = &t;
    auto l = base->Clips();
    CHECK(l.size() == 2);
    auto find1 = std::find(l.begin(), l.end(), &clip1);
    auto find2 = std::find(l.begin(), l.end(), &clip2);
    CHECK(find1 != l.end());
    CHECK(find2 != l.end());
}


TEST_CASE( "Effect order", "[libopenshot][timeline]" )
{
	// Create a timeline
	Timeline t(640, 480, Fraction(30, 1), 44100, 2, LAYOUT_STEREO);

	// Add some effects out of order
	Negate effect_top;
	effect_top.Id("C");
	effect_top.Layer(2);
	t.AddEffect(&effect_top);

	Negate effect_middle;
	effect_middle.Id("A");
	effect_middle.Layer(0);
	t.AddEffect(&effect_middle);

	Negate effect_bottom;
	effect_bottom.Id("B");
	effect_bottom.Layer(1);
	t.AddEffect(&effect_bottom);

	t.Open();

	// Loop through effects and check order (they should have been sorted into the correct order)
	// Bottom layer to top layer, then by position, and then by order.
	std::list<EffectBase*> effects = t.Effects();
	int n = 0;
	for (auto effect : effects) {
		CHECK(effect->Layer() == n);
		CHECK(effect->Order() == 0);
		switch (n) {
		case 0:
			CHECK(effect->Id() == "A");
			break;
		case 1:
			CHECK(effect->Id() == "B");
			break;
		case 2:
			CHECK(effect->Id() == "C");
			break;
		}
		++n;
	}

	// Add some more effects out of order
	Negate effect_top1;
	effect_top1.Id("B-2");
	effect_top1.Layer(1);
	effect_top1.Position(0.5);
	effect_top1.Order(2);
	t.AddEffect(&effect_top1);

	Negate effect_middle1;
	effect_middle1.Id("B-3");
	effect_middle1.Layer(1);
	effect_middle1.Position(0.5);
	effect_middle1.Order(1);
	t.AddEffect(&effect_middle1);

	Negate effect_bottom1;
	effect_bottom1.Id("B-1");
	effect_bottom1.Layer(1);
	effect_bottom1.Position(0);
	effect_bottom1.Order(3);
	t.AddEffect(&effect_bottom1);


	// Loop through effects again, and re-check order
	effects = t.Effects();
	n = 0;
	for (auto effect : effects) {
		switch (n) {
		case 0:
			CHECK(effect->Layer() == 0);
			CHECK(effect->Id() == "A");
			CHECK(effect->Order() == 0);
			break;
		case 1:
			CHECK(effect->Layer() == 1);
			CHECK(effect->Id() == "B-1");
			CHECK(effect->Position() == Approx(0.0).margin(0.0001));
			CHECK(effect->Order() == 3);
			break;
		case 2:
			CHECK(effect->Layer() == 1);
			CHECK(effect->Id() == "B");
			CHECK(effect->Position() == Approx(0.0).margin(0.0001));
			CHECK(effect->Order() == 0);
			break;
		case 3:
			CHECK(effect->Layer() == 1);
			CHECK(effect->Id() == "B-2");
			CHECK(effect->Position() == Approx(0.5).margin(0.0001));
			CHECK(effect->Order() == 2);
			break;
		case 4:
			CHECK(effect->Layer() == 1);
			CHECK(effect->Id() == "B-3");
			CHECK(effect->Position() == Approx(0.5).margin(0.0001));
			CHECK(effect->Order() == 1);
			break;
		case 5:
			CHECK(effect->Layer() == 2);
			CHECK(effect->Id() == "C");
			CHECK(effect->Order() == 0);
			break;
		}
		++n;
	}

	t.Close();
}

TEST_CASE( "GetClip by id", "[libopenshot][timeline]" )
{
	Timeline t(640, 480, Fraction(30, 1), 44100, 2, LAYOUT_STEREO);

	std::stringstream path1;
	path1 << TEST_MEDIA_PATH << "interlaced.png";
	auto media_path1 = path1.str();

	std::stringstream path2;
	path2 << TEST_MEDIA_PATH << "front.png";
	auto media_path2 = path2.str();

	Clip clip1(media_path1);
	std::string clip1_id("CLIP00001");
	clip1.Id(clip1_id);
	clip1.Layer(1);

	Clip clip2(media_path2);
	std::string clip2_id("CLIP00002");
	clip2.Id(clip2_id);
	clip2.Layer(2);
	clip2.Waveform(true);

	t.AddClip(&clip1);
	t.AddClip(&clip2);

	// We explicitly want to get returned a Clip*, here
	Clip* matched = t.GetClip(clip1_id);
	CHECK(matched->Id() == clip1_id);
	CHECK(matched->Layer() == 1);

	Clip* matched2 = t.GetClip(clip2_id);
	CHECK(matched2->Id() == clip2_id);
	CHECK_FALSE(matched2->Layer() < 2);

	Clip* matched3 = t.GetClip("BAD_ID");
	CHECK(matched3 == nullptr);

	// Ensure we can access the Clip API interfaces after lookup
	CHECK_FALSE(matched->Waveform());
	CHECK(matched2->Waveform() == true);
}

TEST_CASE( "GetClipEffect by id", "[libopenshot][timeline]" )
{
	Timeline t(640, 480, Fraction(30, 1), 44100, 2, LAYOUT_STEREO);

	std::stringstream path1;
	path1 << TEST_MEDIA_PATH << "interlaced.png";
	auto media_path1 = path1.str();

	// Create a clip, nothing special
	Clip clip1(media_path1);
	std::string clip1_id("CLIP00001");
	clip1.Id(clip1_id);
	clip1.Layer(1);

	// Add a blur effect
	Keyframe horizontal_radius(5.0);
	Keyframe vertical_radius(5.0);
	Keyframe sigma(3.0);
	Keyframe iterations(3.0);
	Blur blur1(horizontal_radius, vertical_radius, sigma, iterations);
	std::string blur1_id("EFFECT00011");
	blur1.Id(blur1_id);
	clip1.AddEffect(&blur1);

	// A second clip, different layer
	Clip clip2(media_path1);
	std::string clip2_id("CLIP00002");
	clip2.Id(clip2_id);
	clip2.Layer(2);

	// Some effects for clip2
	Negate neg2;
	std::string neg2_id("EFFECT00021");
	neg2.Id(neg2_id);
	neg2.Layer(2);
	clip2.AddEffect(&neg2);
	Blur blur2(horizontal_radius, vertical_radius, sigma, iterations);
	std::string blur2_id("EFFECT00022");
	blur2.Id(blur2_id);
	blur2.Layer(2);
	clip2.AddEffect(&blur2);

	t.AddClip(&clip1);

	// Check that we can look up clip1's effect
	auto match1 = t.GetClipEffect("EFFECT00011");
	CHECK(match1->Id() == blur1_id);

	// clip2 hasn't been added yet, shouldn't be found
	match1 = t.GetClipEffect(blur2_id);
	CHECK(match1 == nullptr);

	t.AddClip(&clip2);

	// Check that blur2 can now be found via clip2
	match1 = t.GetClipEffect(blur2_id);
	CHECK(match1->Id() == blur2_id);
	CHECK(match1->Layer() == 2);
}

TEST_CASE( "GetEffect by id", "[libopenshot][timeline]" )
{
	Timeline t(640, 480, Fraction(30, 1), 44100, 2, LAYOUT_STEREO);

	// Create a timeline effect
	Keyframe horizontal_radius(5.0);
	Keyframe vertical_radius(5.0);
	Keyframe sigma(3.0);
	Keyframe iterations(3.0);
	Blur blur1(horizontal_radius, vertical_radius, sigma, iterations);
	std::string blur1_id("EFFECT00011");
	blur1.Id(blur1_id);
	blur1.Layer(1);
	t.AddEffect(&blur1);

	auto match1 = t.GetEffect(blur1_id);
	CHECK(match1->Id() == blur1_id);
	CHECK(match1->Layer() == 1);

	match1 = t.GetEffect("NOSUCHNAME");
	CHECK(match1 == nullptr);
}

TEST_CASE( "Effect: Blur", "[libopenshot][timeline]" )
{
	// Create a timeline
	Timeline t(640, 480, Fraction(30, 1), 44100, 2, LAYOUT_STEREO);

	std::stringstream path_top;
	path_top << TEST_MEDIA_PATH << "interlaced.png";
	Clip clip_top(path_top.str());
	clip_top.Layer(2);
	t.AddClip(&clip_top);

	// Add some effects out of order
	Keyframe horizontal_radius(5.0);
	Keyframe vertical_radius(5.0);
	Keyframe sigma(3.0);
	Keyframe iterations(3.0);
	Blur blur(horizontal_radius, vertical_radius, sigma, iterations);
	blur.Id("B");
	blur.Layer(2);
	t.AddEffect(&blur);

	// Open Timeline
	t.Open();

	// Get frame
	std::shared_ptr<Frame> f = t.GetFrame(1);

	REQUIRE(f != nullptr);
	CHECK(f->number == 1);

	// Close reader
	t.Close();
}

TEST_CASE( "GetMaxFrame and GetMaxTime", "[libopenshot][timeline]" )
{
	// Create a timeline
	Timeline t(640, 480, Fraction(30, 1), 44100, 2, LAYOUT_STEREO);

	std::stringstream path1;
	path1 << TEST_MEDIA_PATH << "interlaced.png";
	Clip clip1(path1.str());
	clip1.Layer(1);
	clip1.Position(50);
	clip1.End(45);
	t.AddClip(&clip1);

	CHECK(t.GetMaxTime() == Approx(95.0).margin(0.001));
	CHECK(t.GetMaxFrame() == 95 * 30 + 1);

	Clip clip2(path1.str());
	clip2.Layer(2);
	clip2.Position(0);
	clip2.End(55);
	t.AddClip(&clip2);

	CHECK(t.GetMaxFrame() == 95 * 30 + 1);
	CHECK(t.GetMaxTime() == Approx(95.0).margin(0.001));

	clip2.Position(100);
	clip1.Position(80);
	CHECK(t.GetMaxFrame() == 155 * 30 + 1);
	CHECK(t.GetMaxTime() == Approx(155.0).margin(0.001));
	t.RemoveClip(&clip2);
	CHECK(t.GetMaxFrame() == 125 * 30 + 1);
	CHECK(t.GetMaxTime() == Approx(125.0).margin(0.001));
}

TEST_CASE( "Multi-threaded Timeline GetFrame", "[libopenshot][timeline]" )
{
    Timeline *t = new Timeline(1280, 720, Fraction(24, 1), 48000, 2, LAYOUT_STEREO);

    // Large ugly JSON project (4 clips + 3 transitions)
    std::stringstream project_json;
    project_json << "{\"id\":\"CQA0YW6I2Q\",\"fps\":{\"num\":30,\"den\":1},\"display_ratio\":{\"num\":16,\"den\":9},\"pixel_ratio\":{\"num\":1,\"den\":1},\"width\":1280,\"height\":720,\"sample_rate\":48000,\"channels\":2,\"channel_layout\":3,\"settings\":{},\"clips\":[{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"anchor\":0,\"channel_filter\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"channel_mapping\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"display\":0,\"duration\":51.9466667175293,\"effects\":[],\"end\":10.666666666666666,\"gravity\":4,\"has_audio\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"has_video\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"id\":\"QHESI4ZW0E\",\"layer\":5000000,\"location_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"location_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"mixing\":0,\"origin_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"origin_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"parentObjectId\":\"\",\"perspective_c1_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c1_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"position\":0,\"reader\":{\"acodec\":\"aac\",\"audio_bit_rate\":126694,\"audio_stream_index\":1,\"audio_timebase\":{\"den\":48000,\"num\":1},\"channel_layout\":3,\"channels\":2,\"display_ratio\":{\"den\":9,\"num\":16},\"duration\":51.9466667175293,\"file_size\":\"7608204\",\"fps\":{\"den\":1,\"num\":24},\"has_audio\":true,\"has_single_image\":false,\"has_video\":true,\"height\":720,\"interlaced_frame\":false,\"metadata\":{\"artist\":\"Durian Open Movie Team\",\"compatible_brands\":\"isomiso2avc1mp41\",\"copyright\":\"(c) copyright Blender Foundation | durian.blender.org\",\"creation_time\":\"1970-01-01T00:00:00.000000Z\",\"description\":\"Trailer for the Sintel open movie project\",\"encoder\":\"Lavf52.62.0\",\"handler_name\":\"SoundHandler\",\"language\":\"und\",\"major_brand\":\"isom\",\"minor_version\":\"512\",\"title\":\"Sintel Trailer\"},\"path\":\"" << TEST_MEDIA_PATH << "sintel_trailer-720p.mp4\",\"pixel_format\":0,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":48000,\"top_field_first\":true,\"type\":\"FFmpegReader\",\"vcodec\":\"h264\",\"video_bit_rate\":145725,\"video_length\":\"1253\",\"video_stream_index\":0,\"video_timebase\":{\"den\":24,\"num\":1},\"width\":1280},\"rotation\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale\":1,\"scale_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"start\":0,\"time\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"volume\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"wave_color\":{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"blue\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"green\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":123},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"red\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]}},\"waveform\":false,\"file_id\":\"XL7T80Y9R1\",\"title\":\"sintel_trailer-720p.mp4\",\"image\":\"@assets/thumbnail/XL7T80Y9R1.png\"},{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"anchor\":0,\"channel_filter\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"channel_mapping\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"display\":0,\"duration\":51.9466667175293,\"effects\":[],\"end\":20.866666666666667,\"gravity\":4,\"has_audio\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"has_video\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"layer\":5000000,\"location_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"location_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"mixing\":0,\"origin_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"origin_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"parentObjectId\":\"\",\"perspective_c1_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c1_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"position\":5.7,\"reader\":{\"acodec\":\"aac\",\"audio_bit_rate\":126694,\"audio_stream_index\":1,\"audio_timebase\":{\"den\":48000,\"num\":1},\"channel_layout\":3,\"channels\":2,\"display_ratio\":{\"den\":9,\"num\":16},\"duration\":51.9466667175293,\"file_size\":\"7608204\",\"fps\":{\"den\":1,\"num\":24},\"has_audio\":true,\"has_single_image\":false,\"has_video\":true,\"height\":720,\"interlaced_frame\":false,\"metadata\":{\"artist\":\"Durian Open Movie Team\",\"compatible_brands\":\"isomiso2avc1mp41\",\"copyright\":\"(c) copyright Blender Foundation | durian.blender.org\",\"creation_time\":\"1970-01-01T00:00:00.000000Z\",\"description\":\"Trailer for the Sintel open movie project\",\"encoder\":\"Lavf52.62.0\",\"handler_name\":\"SoundHandler\",\"language\":\"und\",\"major_brand\":\"isom\",\"minor_version\":\"512\",\"title\":\"Sintel Trailer\"},\"path\":\"" << TEST_MEDIA_PATH << "sintel_trailer-720p.mp4\",\"pixel_format\":0,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":48000,\"top_field_first\":true,\"type\":\"FFmpegReader\",\"vcodec\":\"h264\",\"video_bit_rate\":145725,\"video_length\":\"1253\",\"video_stream_index\":0,\"video_timebase\":{\"den\":24,\"num\":1},\"width\":1280},\"rotation\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale\":1,\"scale_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"start\":10.666666666666666,\"time\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"volume\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"wave_color\":{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"blue\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"green\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":123},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"red\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]}},\"waveform\":false,\"file_id\":\"XL7T80Y9R1\",\"title\":\"sintel_trailer-720p.mp4\",\"id\":\"KQK39ZFGJE\",\"image\":\"@assets/thumbnail/XL7T80Y9R1.png\"},{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"anchor\":0,\"channel_filter\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"channel_mapping\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"display\":0,\"duration\":51.9466667175293,\"effects\":[],\"end\":29.566666666666666,\"gravity\":4,\"has_audio\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"has_video\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"layer\":5000000,\"location_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"location_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"mixing\":0,\"origin_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"origin_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"parentObjectId\":\"\",\"perspective_c1_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c1_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"position\":12.3,\"reader\":{\"acodec\":\"aac\",\"audio_bit_rate\":126694,\"audio_stream_index\":1,\"audio_timebase\":{\"den\":48000,\"num\":1},\"channel_layout\":3,\"channels\":2,\"display_ratio\":{\"den\":9,\"num\":16},\"duration\":51.9466667175293,\"file_size\":\"7608204\",\"fps\":{\"den\":1,\"num\":24},\"has_audio\":true,\"has_single_image\":false,\"has_video\":true,\"height\":720,\"interlaced_frame\":false,\"metadata\":{\"artist\":\"Durian Open Movie Team\",\"compatible_brands\":\"isomiso2avc1mp41\",\"copyright\":\"(c) copyright Blender Foundation | durian.blender.org\",\"creation_time\":\"1970-01-01T00:00:00.000000Z\",\"description\":\"Trailer for the Sintel open movie project\",\"encoder\":\"Lavf52.62.0\",\"handler_name\":\"SoundHandler\",\"language\":\"und\",\"major_brand\":\"isom\",\"minor_version\":\"512\",\"title\":\"Sintel Trailer\"},\"path\":\"" << TEST_MEDIA_PATH << "sintel_trailer-720p.mp4\",\"pixel_format\":0,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":48000,\"top_field_first\":true,\"type\":\"FFmpegReader\",\"vcodec\":\"h264\",\"video_bit_rate\":145725,\"video_length\":\"1253\",\"video_stream_index\":0,\"video_timebase\":{\"den\":24,\"num\":1},\"width\":1280},\"rotation\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale\":1,\"scale_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"start\":20.866666666666667,\"time\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"volume\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"wave_color\":{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"blue\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"green\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":123},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"red\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]}},\"waveform\":false,\"file_id\":\"XL7T80Y9R1\",\"title\":\"sintel_trailer-720p.mp4\",\"id\":\"TMKI8CK7QQ\",\"image\":\"@assets/thumbnail/XL7T80Y9R1.png\"},{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0},{\"co\":{\"X\":91,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0},{\"co\":{\"X\":541,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0},{\"co\":{\"X\":631,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"anchor\":0,\"channel_filter\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"channel_mapping\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"display\":0,\"duration\":3600,\"effects\":[],\"end\":21,\"gravity\":4,\"has_audio\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"has_video\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"id\":\"2CQVCHPATF\",\"layer\":6000000,\"location_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"location_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"mixing\":0,\"origin_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"origin_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0.5},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"parentObjectId\":\"\",\"perspective_c1_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c1_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c2_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c3_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"perspective_c4_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"position\":0,\"reader\":{\"acodec\":\"\",\"audio_bit_rate\":0,\"audio_stream_index\":-1,\"audio_timebase\":{\"den\":1,\"num\":1},\"channel_layout\":4,\"channels\":0,\"display_ratio\":{\"den\":2,\"num\":3},\"duration\":3600,\"file_size\":\"1382400\",\"fps\":{\"den\":1,\"num\":30},\"has_audio\":false,\"has_single_image\":true,\"has_video\":true,\"height\":480,\"interlaced_frame\":false,\"metadata\":{},\"path\":\"" << TEST_MEDIA_PATH << "front3.png\",\"pixel_format\":-1,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":0,\"top_field_first\":true,\"type\":\"QtImageReader\",\"vcodec\":\"\",\"video_bit_rate\":0,\"video_length\":\"108000\",\"video_stream_index\":-1,\"video_timebase\":{\"den\":30,\"num\":1},\"width\":720},\"rotation\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale\":1,\"scale_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"scale_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_x\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"shear_y\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"start\":0,\"time\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"volume\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"wave_color\":{\"alpha\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"blue\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":255},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"green\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":123},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"red\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":0},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]}},\"waveform\":false,\"file_id\":\"RY3OYWU7HK\",\"title\":\"front3.png\",\"image\":\"@assets/thumbnail/RY3OYWU7HK.png\"}],\"effects\":[{\"id\":\"335XHEZJNX\",\"layer\":5000000,\"title\":\"Transition\",\"type\":\"Mask\",\"position\":5.7,\"start\":0,\"end\":4.966666666666666,\"brightness\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0},{\"co\":{\"X\":150,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"contrast\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":3},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"reader\":{\"acodec\":\"\",\"audio_bit_rate\":0,\"audio_stream_index\":-1,\"audio_timebase\":{\"den\":1,\"num\":1},\"channel_layout\":4,\"channels\":0,\"display_ratio\":{\"den\":4,\"num\":5},\"duration\":3600,\"file_size\":\"5832000\",\"fps\":{\"den\":1,\"num\":30},\"has_audio\":false,\"has_single_image\":true,\"has_video\":true,\"height\":576,\"interlaced_frame\":false,\"metadata\":{},\"path\":\"" << TEST_MEDIA_PATH << "mask.png\",\"pixel_format\":-1,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":0,\"top_field_first\":true,\"type\":\"QtImageReader\",\"vcodec\":\"\",\"video_bit_rate\":0,\"video_length\":\"108000\",\"video_stream_index\":-1,\"video_timebase\":{\"den\":30,\"num\":1},\"width\":720},\"replace_image\":false},{\"id\":\"QQECKBIYUP\",\"layer\":5000000,\"title\":\"Transition\",\"type\":\"Mask\",\"position\":12.3,\"start\":0,\"end\":3.6000000000000014,\"brightness\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0},{\"co\":{\"X\":109,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"contrast\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":3},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"reader\":{\"acodec\":\"\",\"audio_bit_rate\":0,\"audio_stream_index\":-1,\"audio_timebase\":{\"den\":1,\"num\":1},\"channel_layout\":4,\"channels\":0,\"display_ratio\":{\"den\":4,\"num\":5},\"duration\":3600,\"file_size\":\"5832000\",\"fps\":{\"den\":1,\"num\":30},\"has_audio\":false,\"has_single_image\":true,\"has_video\":true,\"height\":576,\"interlaced_frame\":false,\"metadata\":{},\"path\":\"" << TEST_MEDIA_PATH << "mask.png\",\"pixel_format\":-1,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":0,\"top_field_first\":true,\"type\":\"QtImageReader\",\"vcodec\":\"\",\"video_bit_rate\":0,\"video_length\":\"108000\",\"video_stream_index\":-1,\"video_timebase\":{\"den\":30,\"num\":1},\"width\":720},\"replace_image\":false},{\"id\":\"YELU1J5KI8\",\"layer\":5000000,\"title\":\"Transition\",\"type\":\"Mask\",\"position\":17.7,\"start\":0,\"end\":3.3000000000000007,\"brightness\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0},{\"co\":{\"X\":100,\"Y\":-1},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"contrast\":{\"Points\":[{\"co\":{\"X\":1,\"Y\":3},\"handle_left\":{\"X\":0.5,\"Y\":1},\"handle_right\":{\"X\":0.5,\"Y\":0},\"handle_type\":0,\"interpolation\":0}]},\"reader\":{\"acodec\":\"\",\"audio_bit_rate\":0,\"audio_stream_index\":-1,\"audio_timebase\":{\"den\":1,\"num\":1},\"channel_layout\":4,\"channels\":0,\"display_ratio\":{\"den\":4,\"num\":5},\"duration\":3600,\"file_size\":\"5832000\",\"fps\":{\"den\":1,\"num\":30},\"has_audio\":false,\"has_single_image\":true,\"has_video\":true,\"height\":576,\"interlaced_frame\":false,\"metadata\":{},\"path\":\"" << TEST_MEDIA_PATH << "mask.png\",\"pixel_format\":-1,\"pixel_ratio\":{\"den\":1,\"num\":1},\"sample_rate\":0,\"top_field_first\":true,\"type\":\"QtImageReader\",\"vcodec\":\"\",\"video_bit_rate\":0,\"video_length\":\"108000\",\"video_stream_index\":-1,\"video_timebase\":{\"den\":30,\"num\":1},\"width\":720},\"replace_image\":false}],\"duration\":300,\"scale\":15,\"tick_pixels\":100,\"playhead_position\":0,\"profile\":\"HD 720p 30 fps\",\"layers\":[{\"id\":\"L1\",\"label\":\"\",\"number\":1000000,\"y\":0,\"lock\":false},{\"id\":\"L2\",\"label\":\"\",\"number\":2000000,\"y\":0,\"lock\":false},{\"id\":\"L3\",\"label\":\"\",\"number\":3000000,\"y\":0,\"lock\":false},{\"id\":\"L4\",\"label\":\"\",\"number\":4000000,\"y\":0,\"lock\":false},{\"id\":\"L5\",\"label\":\"\",\"number\":5000000,\"y\":0,\"lock\":false},{\"number\":6000000,\"y\":0,\"label\":\"\",\"lock\":false,\"id\":\"4U4NB9QVD2\"}],\"markers\":[],\"progress\":[],\"version\":{\"openshot-qt\":\"2.6.1-dev\",\"libopenshot\":\"0.2.7-dev\"}}";
    t->SetJson(project_json.str());
    t->Open();

    // A successful test will not crash - since this causes many threads to
    // call the same Timeline::GetFrame method, to verify mutexes and multi-threaded
    // access does not seg fault or crash this test.
#pragma omp parallel
    {
        // Run the following loop in all threads
        int64_t frame_count = 60;
        for (long int frame = 1; frame <= frame_count; frame++) {
            std::shared_ptr<Frame> f = t->GetFrame(frame);
        }

    }

    // Close and delete timeline object
    t->Clear();
    t->Close();
    delete t;
    t = NULL;
}