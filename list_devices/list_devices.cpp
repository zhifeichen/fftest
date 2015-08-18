#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#ifdef __cplusplus
};
#endif

int main(int argc, char* argv[])
{
	AVFormatContext *pFormatCtx;
	AVDeviceInfoList*pDeviceList;
	AVInputFormat *ifmt;
	AVDictionary* options = NULL;
	AVOutputFormat *ofmt;

	av_register_all();
	avdevice_register_all();

	pFormatCtx = avformat_alloc_context();
	av_dict_set(&options, "list_devices", "true", 0);
	ifmt = av_find_input_format("gdigrab");
	if (avformat_open_input(&pFormatCtx, "title=D:\\project\\fftest\\fftest\\bin\\list_devices.exe", ifmt, &options) != 0) {
		printf("open dshow error\n");
		//return -1;
	}
	//pFormatCtx->iformat = ifmt;
	avdevice_list_devices(pFormatCtx, &pDeviceList);
	avdevice_list_input_sources(ifmt, "desktop", options, &pDeviceList);

	ofmt = av_guess_format("dshow", NULL, NULL);
	avdevice_list_output_sinks(ofmt, NULL, NULL, &pDeviceList);
	return 0;
}