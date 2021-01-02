#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<unistd.h>
#include<signal.h>
#include<stdint.h>

Mix_Chunk*snd;

// Initialize audio 
void init(void);
// Close audio
void quit(void);
// Handle ^C
void sh(int s);
// Exit on error
void die(const char*msg);

int main(int argc,char**argv)
{
	uint32_t delay_bpm=60;
	uint32_t measure=4;

	init();

	// Parse arguments
	if(argc>1)
	{
		if(strncmp(argv[1],"--help",16)==0)
			die("usage: met [BPM [TIMESIG]]");
		sscanf(argv[1],"%d",&delay_bpm);
		if(delay_bpm<1)die("error: too small frequency");
	}

	if(argc>2)
	{
		sscanf(argv[2],"%d",&measure);
		if(measure<1)die("error: bad time signature");
	}


	// Metronome loop
	for(uint32_t i=0;;++i)
	{
		printf("\r[ %u bpm ] [ beat %u ]",delay_bpm,i%measure+1);
		fflush(stdout);
		Mix_PlayChannel(0,snd,0);
		usleep(60.0/delay_bpm*1000*1000);
	}

	quit();
}

void sh(int s)
{
	quit();
	exit(0);
}

void quit(void)
{
	//puts("\rExiting gracefully");
	puts("\r");
	if(snd)
		Mix_FreeChunk(snd);
	Mix_Quit();
}

void init(void)
{
	signal(SIGINT,sh);
	Mix_Init(MIX_INIT_MOD);

	Mix_OpenAudio(44100,AUDIO_S16SYS,2,512);
	Mix_AllocateChannels(4);

	snd=Mix_LoadWAV("click.wav");
}

void die(const char*msg)
{
	puts(msg);
	quit();
}
