#ifdef __cplusplus
extern "C"{
#endif

#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>

#ifdef __cplusplus
};
#endif

#define USE_MP3 1
#define USE_AAC 0

int main(int argc, char* argv[])
{
	AVCodec *pCodec;
	AVCodecContext *pCodecCtx = NULL;
	AVCodecParserContext *pCodecParserCtx = NULL;

	FILE *fp_in;
	FILE *fp_out;
	AVFrame	*pFrame;

	const int in_buffer_size = 4096;
	uint8_t in_buffer[in_buffer_size + FF_INPUT_BUFFER_PADDING_SIZE] = { 0 };
	uint8_t *cur_ptr;
	int cur_size;
	AVPacket packet;
	int ret, got_picture;
	int y_size;

#if USE_MP3
	AVCodecID codec_id = AV_CODEC_ID_MP3; // AV_CODEC_ID_AAC;
	char filepath_in[] = "../testResource/skycity1.mp3"; // "../testResource/WavinFlag.aac";
#elif USE_AAC
	AVCodecID codec_id = AV_CODEC_ID_AAC;
	char filepath_in[] = "../testResource/WavinFlag.aac";
#endif

	char filepath_out[] = "WavinFlag.pcm";
	int first_time = 1;

	avcodec_register_all();

	pCodec = avcodec_find_decoder(codec_id);
	if (!pCodec) {
		printf("Codec not found\n");
		return -1;
	}
	pCodecCtx = avcodec_alloc_context3(pCodec);
	if (!pCodecCtx) {
		printf("Could not allocate audio codec context\n");
		return -1;
	}

	pCodecParserCtx = av_parser_init(codec_id);
	if (!pCodecParserCtx) {
		printf("Could not allocate audio parser context\n");
		return -1;
	}
	pCodecParserCtx->flags |= PARSER_FLAG_COMPLETE_FRAMES;

	//AVBitStreamFilterContext* bsfc = av_bitstream_filter_init("mp3decomp");

	//if(pCodec->capabilities&CODEC_CAP_TRUNCATED)
	//    pCodecCtx->flags|= CODEC_FLAG_TRUNCATED; /* we do not send complete frames */

	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
		printf("Could not open codec\n");
		return -1;
	}
	//Input File
	fp_in = fopen(filepath_in, "rb");
	if (!fp_in) {
		printf("Could not open input stream\n");
		return -1;
	}
	//Output File
	fp_out = fopen(filepath_out, "wb");
	if (!fp_out) {
		printf("Could not open output PCM file\n");
		return -1;
	}

	pFrame = av_frame_alloc();
	av_init_packet(&packet);
	int index = 0;
	while (1) {

		cur_size = fread(in_buffer, 1, in_buffer_size, fp_in);
		if (cur_size == 0)
			break;
		cur_ptr = in_buffer;

		while (cur_size>0) {

			//ret = av_bitstream_filter_filter(bsfc, pCodecCtx, NULL, &cur_ptr, &cur_size, cur_ptr, cur_size, 0);
			//if (ret < 0) {
			//	char err[64];
			//	av_strerror(ret, err, 64);
			//	printf("av_bitstream_filter_filter Error: %s\n", err);
			//	//break;
			//}

			int len = av_parser_parse2(
				pCodecParserCtx, pCodecCtx,
				&packet.data, &packet.size,
				cur_ptr, cur_size,
				AV_NOPTS_VALUE, AV_NOPTS_VALUE, AV_NOPTS_VALUE);

			cur_ptr += len;
			cur_size -= len;

			if (packet.size == 0)
				continue;

			//Some Info from AVCodecParserContext
			printf("[Packet]Size:%6d\t", packet.size);

			printf("Number:%4d\n", pCodecParserCtx->output_picture_number);

			//ret = av_bitstream_filter_filter(bsfc, pCodecCtx, NULL, &packet.data, &packet.size, packet.data, packet.size, 0);
			//if (ret < 0) {
			//	char err[64];
			//	av_strerror(ret, err, 64);
			//	printf("av_bitstream_filter_filter Error: %s\n", err);
			//	break;
			//}

			ret = avcodec_decode_audio4(pCodecCtx, pFrame, &got_picture, &packet);
			//av_free_packet(&packet);
			if (ret < 0) {
				char err[64];
				av_strerror(ret, err, 64);
				printf("Decode Error: %s\n", err);
				//break;
			}
			if (got_picture) {

				printf("index:%5d\t pts:%lld\t packet size:%d\n", index++, packet.pts, pFrame->nb_samples);
				AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16; (AVSampleFormat)pFrame->format;  AV_SAMPLE_FMT_FLTP; AV_SAMPLE_FMT_S16;
				int out_sample_rate = pFrame->sample_rate;
				uint64_t out_channel_layout = pFrame->channel_layout; // AV_CH_LAYOUT_STEREO; // pFrame->channels;
				int out_buffer_size = av_samples_get_buffer_size(NULL, pFrame->channels, pFrame->nb_samples, out_sample_fmt, 1);
				uint64_t in_channel_layout = pCodecCtx->channel_layout;
				AVSampleFormat in_sample_fmt = pCodecCtx->sample_fmt;
				int in_sample_rate = pCodecCtx->sample_rate;
			}
			av_free_packet(&packet);
		}

	}

	//Flush Decoder
	//packet.data = NULL;
	//packet.size = 0;
	av_free_packet(&packet);
	while (1) {
		ret = avcodec_decode_audio4(pCodecCtx, pFrame, &got_picture, &packet);
		av_free_packet(&packet);
		if (ret < 0) {
			printf("Decode Error.\n");
			break;
		}
		if (!got_picture)
			break;
		if (got_picture) {
			printf("index:%5d\t pts:%lld\t packet size:%d\n", index++, pFrame->pts, pFrame->nb_samples);
		}
	}

	fclose(fp_in);
	fclose(fp_out);

	av_parser_close(pCodecParserCtx);

	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	av_free(pCodecCtx);
	return 0;
}