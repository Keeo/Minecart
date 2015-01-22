#pragma once

enum EEvent {

	SetCameraPosRot,

	Shutdown,
		
	FetchCameraData,

	BuildMeshForChunk,

	ReorderChunkArray,
	RebuildChunkArray,

	CameraChangedChunk,

	COUNT
};
