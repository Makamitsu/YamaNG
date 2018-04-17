#pragma once

struct GLFWwindow;

namespace yama {
	namespace graphics {


		class Window
		{

		private:
			int mWidth;
			int mHeight;
			const char* mTitle;
			GLFWwindow* mWindow;
			bool mClosed;

		public:
			Window(const char* pName, int pWidth, int pHeight);
			~Window();
			void update();
			void clear();
			bool closed();

			inline int getWidth() const { return mWidth; };
			inline int getHeight() const { return mHeight; };

			Window(const Window&) = delete;
		private:

			bool init();

		};



	}
}





