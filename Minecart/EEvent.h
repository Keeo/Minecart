#pragma once

enum EEvent {

	SetCameraPosRot,

	Shutdown,

	FetchCameraData,

	BuildMeshForChunk,

	ReorderChunkArray,
	RebuildChunkArray,
	RelinkChunkArray,

	CameraChangedChunk,

	FillChunks,
	RebuildVisbility,

	COUNT
};
