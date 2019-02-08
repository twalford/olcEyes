#include "olcPixelGameEngine.h"

struct Pos
{
public:
	Pos() {}
	Pos(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	float x;
	float y;
};

struct Eye
{
public:
	Eye() {}
	Eye(float _x, float _y) 
	{
		pos.x = _x;
		pos.y = _y;
	}

	Pos pos;
	Pos pupil;

};

class olcEyes : public olc::PixelGameEngine
{
public:
	olcEyes()
	{
		sAppName = "Eyes";
	}

	float timeAcc = 0;
	Eye eyeLeft = Eye(240, 240);
	Eye eyeRight = Eye(400, 240);
	short nEyeRadius = 40;
	short nPupilRadius = 16;
	float lookAmount = 28.0f;

	float eyeZoffset = 0;
	float eyeZ[23][44] = { 0 };
	short eyeMask[23][44] =
	{
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,2,1,1,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,1,2,2,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,2,1,2,2,2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,1,2,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,1,1,2,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,2 },
		{ 2,2,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2 },
		{ 1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2 },
		{ 2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,2 },
		{ 2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,2 },
		{ 2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2 },
		{ 2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2 },
		{ 2,2,2,2,2,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2 },
		{ 2,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2 },
		{ 2,2,2,2,2,2,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1 },
		{ 2,2,2,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1 },
		{ 2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1 },
		{ 2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,2 },
		{ 2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2 }
	};

	float irisZ[16][18] = { 0 };
	float irisMask[16][18] =
	{
		{ 0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0 },
		{ 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0 },
		{ 0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0 },
		{ 0,1,1,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0 },
		{ 0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0 },
		{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1 },
		{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1 },
		{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1 },
		{ 1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1 },
		{ 0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0 },
		{ 0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0 },
		{ 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0 },
		{ 0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0 },
		{ 0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0 },
		{ 0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0 }
	};

	float pupilZ[4][5] = { 0 };
	short pupilMask[4][5] =
	{
		{0,1,0,1,0},
		{1,1,1,1,1},
		{1,1,1,1,1},
		{0,1,1,1,0}
	};

	float posX = 0;
	float posY = 0;

	olc::Pixel cBackground = olc::Pixel(0, 0, 0);
	olc::Pixel cEye = olc::Pixel(0, 180, 180);
	olc::Pixel cIris = olc::Pixel(51, 255, 255);
	olc::Pixel cPupil = olc::Pixel(51, 255, 255);

	// bright cyan		olc::Pixel(209, 255, 255));
	// mid blue			olc::Pixel(6, 43, 91));

	bool OnUserCreate() override
	{
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(6, 43, 91));
		
		//eye
		for (int ey = 0; ey < 23; ey++)
			for (int ex = 0; ex < 44; ex++)
				if (eyeMask[ey][ex] == 1)
				{
					eyeZ[ey][ex] = 0.3f;
					float neighbourCount = 0.0f;

					if (ey > 0  && eyeMask[ey - 1][ex] == 1) neighbourCount += 1.0f;
					if (ey < 22 && eyeMask[ey + 1][ex] == 1) neighbourCount += 1.0f;
					if (ex > 0  && eyeMask[ey][ex - 1] == 1) neighbourCount += 1.0f;
					if (ex < 43 && eyeMask[ey][ex + 1] == 1) neighbourCount += 1.0f;

					eyeZ[ey][ex] = neighbourCount * 0.15f;
					eyeZ[ey][ex] += (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 0.5f;
				}

		//iris
		for (int iy = 0; iy < 16; iy++)
			for (int ix = 0; ix < 18; ix++)
				if (irisMask[iy][ix] == 1)
				{
					irisZ[iy][ix] = 0.3f;
					float neighbourCount = 0.0f;

					if (iy > 0  && irisMask[iy - 1][ix] == 1) neighbourCount += 1.0f;
					if (iy < 15 && irisMask[iy + 1][ix] == 1) neighbourCount += 1.0f;
					if (ix > 0  && irisMask[iy][ix - 1] == 1) neighbourCount += 1.0f;
					if (ix < 17 && irisMask[iy][ix + 1] == 1) neighbourCount += 1.0f;

					irisZ[iy][ix] = neighbourCount * 0.15f;
					irisZ[iy][ix] += (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 0.5f;
				}

		//pupil
		for (int py = 0; py < 4; py++)
			for (int px = 0; px < 5; px++)
				if (pupilMask[py][px] == 1)
				{
					pupilZ[py][px] = 0.3f;
					float neighbourCount = 0.0f;

					if (py > 0 && pupilMask[py - 1][px] == 1) neighbourCount += 1.0f;
					if (py < 3 && pupilMask[py + 1][px] == 1) neighbourCount += 1.0f;
					if (px > 0 && pupilMask[py][px - 1] == 1) neighbourCount += 1.0f;
					if (px < 4 && pupilMask[py][px + 1] == 1) neighbourCount += 1.0f;

					pupilZ[py][px] = neighbourCount * 0.15f;
					pupilZ[py][px] += (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 0.5f;
				}

		return true;
	}

	bool OnUserUpdate(float fElapedTime) override
	{
		//timing
		timeAcc += fElapedTime;

		//input

		//logic
		float mouseXn = ((float)GetMouseX() / (float)ScreenWidth()) - 0.5;
		float mouseYn = ((float)GetMouseY() / (float)ScreenHeight()) - 0.5;
		float mXnL = mouseXn + 0.20;
		float mYnL = mouseYn + 0.07;
		float mXnR = mouseXn - 0.20;
		float mYnR = mouseYn + 0.07;


		//Drawing
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), cBackground);

		eyeZoffset = sinf(timeAcc * 0.6f) * 0.2f + 0.2f;
		
		//pupil
		for (int py = 0; py < 4; py++)
			for (int px = 0; px < 5; px++)
				if (pupilMask[py][px] == 1)
				{

					FillSquareRadius(px * 9 + 369 + (mXnL * lookAmount * 6.0f), py * 9 + 281 + (mYnL * lookAmount * 1.5f), (pupilZ[py][px] + eyeZoffset) * 2.4f, cPupil);
					FillSquareRadius((4 - px) * 9 + 902 + (mXnR * lookAmount * 6.0f), py * 9 + 281 + (mYnR * lookAmount * 1.5f), (pupilZ[py][px] + eyeZoffset) * 2.4f, cPupil);
				}

		//iris
		for (int iy = 0; iy < 16; iy++)
			for (int ix = 0; ix < 18; ix++)
				if (irisMask[iy][ix] == 1)
				{
					FillSquareRadius(ix * 9 + 306 + (mXnL * lookAmount * 5.0f), iy * 9 + 236 + (mYnL * lookAmount), (irisZ[iy][ix] + eyeZoffset) * 2.4f, cIris);
					FillSquareRadius((17 - ix) * 9 + 848 + (mXnR * lookAmount * 5.0f), iy * 9 + 236 + (mYnR * lookAmount), (irisZ[iy][ix] + eyeZoffset) * 2.4f, cIris);
				}

		//eye
		for (int ey = 0; ey < 23; ey++)
			for(int ex = 0; ex < 44; ex++)
				if (eyeMask[ey][ex] == 1)
				{
					FillSquareRadius(ex * 9 + 180, ey * 9 + 200, 4, cBackground);
					FillSquareRadius((43 - ex) * 9 + 740, ey * 9 + 200, 4, cBackground);
					FillSquareRadius(ex * 9 + 180, ey * 9 + 200, (eyeZ[ey][ex] + eyeZoffset) * 2.4f, cEye);
					FillSquareRadius((43 - ex) * 9 + 740, ey * 9 + 200, (eyeZ[ey][ex] + eyeZoffset) * 2.4f, cEye);
				}
				else if (eyeMask[ey][ex] == 2)
				{
					FillSquareRadius(ex * 9 + 180, ey * 9 + 200, 4, cBackground);
					FillSquareRadius((43 - ex) * 9 + 740, ey * 9 + 200, 4, cBackground);
				}
		
		//strings
		//DrawString(1, 1, "Mouse:   " + std::to_string(GetMouseX()) + "  " + std::to_string(GetMouseY()));
		//DrawString(1, 9, "MouseN:  " + std::to_string(mouseXn) + "  " + std::to_string(mouseYn));

		DrawString(618, 300, "Continue");
		DrawString(618, 330, "New Game");
		DrawString(618, 360, "Settings");
		DrawString(618, 390, "  Quit  ");

		return true;
	}

	void FillSquareRadius(int32_t x, int32_t y, float radius, olc::Pixel p)
	{
		int s = radius + radius + 1.0f;
		FillRect(x - radius, y - radius, s, s, p);
	}

};

int main()
{
	olcEyes demo;
	if (demo.Construct(1300, 680, 1, 1))
		demo.Start();

	return 0;
}