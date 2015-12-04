#ifndef VIEW_CONTROLLER
#define VIEW_CONTROLLER



namespace parview
{
	class view_controller
	{
	public:
		view_controller();
		~view_controller();

		static bool is_end_frame();
		static void move2previous2x();
		static void move2previous1x();
		static void on_play();
		static bool Play();
		static void off_play();
		static void move2forward1x();
		static void move2forward2x();
		static unsigned int getTotalBuffers() { return buffer_count; }
		static void setFrame(unsigned int f) { current_frame = f; }
		static int getFrame() { return (int)current_frame; }
		static void upBufferCount() { buffer_count++;  }
		static void addTimes(double time) { times[buffer_count] = time; }
		static double getTimes() { return times[current_frame]; }
		static void setTotalFrame(unsigned int tf) { buffer_count = tf; }
		static void setRealTimeParameter(bool rt) { real_time = rt; }
		static bool getRealTimeParameter() { return real_time; }

	private:
		static unsigned int current_frame;
		static unsigned int buffer_count;
		static bool is_play;
		static bool real_time;
		static double *times;
	};
}

#endif