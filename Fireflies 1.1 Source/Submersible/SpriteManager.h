#pragma once

#if !defined(__SpriteManager_H__)
#define __SpriteManager_H__

// Library Includes

#include "AnimatedSprite.h"
#include "SpriteDataShell.h"
#include <vector>


// Local Includes

// Types

// Constants

// Prototypes


class CSpriteManager
{
// Member Functions
public:
	CSpriteManager();
	~CSpriteManager();
	void Initialise();
	void Draw(CSpriteDataShell* _pSDS);
	void DrawList();
	void AddToDrawList(CSpriteDataShell* _pSDS);
	void SetDrawOffset(float _fX, float _fY);

	void SetZoom(float _fZoom){m_fZoom = _fZoom;};
	float GetZoom(){return(m_fZoom);};
	void AdjustZoom(float _fZoomAdjustment){m_fZoom += _fZoomAdjustment;};

	void SetDrawOffsetX(float _fDrawOffsetX){m_fDrawOffsetX = _fDrawOffsetX;};
	float GetDrawOffsetX(){return(m_fDrawOffsetX);};
	void AdjustDrawOffsetX(float _fDrawOffsetXAdjustment){m_fDrawOffsetX += _fDrawOffsetXAdjustment;};

	void SetDrawOffsetY(float _fDrawOffsetY){m_fDrawOffsetY = _fDrawOffsetY;};
	float GetDrawOffsetY(){return(m_fDrawOffsetY);};
	void AdjustDrawOffsetY(float _fDrawOffsetYAdjustment){m_fDrawOffsetY += _fDrawOffsetYAdjustment;};

	void BeginBatch(ESpriteID _SpriteID);
	void EndBatch();

	bool IsBatchDrawing(){return(m_bBatchDrawing);};

	int GetTotalFrames(ESpriteID _SpriteID);

	unsigned int GetHeight(ESpriteID _SpriteID);
	unsigned int GetWidth(ESpriteID _SpriteID);

	void OnLostDevice();
	void OnResetDevice();

protected:

private:

// Member Variables
public:
	
protected:

	float m_fDrawOffsetX;
	float m_fDrawOffsetY;
	float m_fZoom;
	bool m_bBatchDrawing;
	ESpriteID m_BatchSpriteID;
	std::vector<CAnimatedSprite*> m_SpriteVec;
	std::vector<CSpriteDataShell*> m_DrawList;


private:

};

#endif // __SpriteManager_H__
