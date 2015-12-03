#include "view_controller.h"
#include "Object.h"

using namespace parview;

unsigned int view_controller::current_frame = 0;
unsigned int view_controller::buffer_count = 0;
bool view_controller::is_play = false;
double *view_controller::times = new double[MAX_FRAME];
bool view_controller::real_time = false;

view_controller::view_controller()
{

}

view_controller::~view_controller()
{
	if (times) delete[] times; times = NULL;
}

bool view_controller::is_end_frame()
{
	if (is_play){
		/*current_frame++;*/
		if (current_frame > buffer_count-1){
			current_frame = buffer_count-1;
			return true;
		}
	}
	
	return false;
}

void view_controller::move2previous2x()
{
	current_frame ? (--current_frame ? --current_frame : current_frame = 0) : current_frame = 0;
}

void view_controller::move2previous1x()
{
	current_frame ? --current_frame : current_frame = 0;
}

void view_controller::on_play()
{
	is_play = true;
}

bool view_controller::Play()
{
	return is_play;
}

void view_controller::off_play()
{
	is_play = false;
}

void view_controller::move2forward1x()
{
	current_frame == buffer_count-1 ? current_frame = current_frame : ++current_frame;
}

void view_controller::move2forward2x()
{
	current_frame == buffer_count-1 ? current_frame = current_frame : (++current_frame == buffer_count-1 ? current_frame = current_frame : ++current_frame);
}