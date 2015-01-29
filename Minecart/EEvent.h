#pragma once

enum EEvent {

	SetCameraPosRot,

	Shutdown,

	FetchCameraData,

	BuildMeshForChunk,

	ReorderDrawVector,
	RebuildDrawVector,

	WatcherInit,
	WatcherMove,
	WatcherChange,

	CameraChangedChunk,

	FillChunks,
	RebuildVisbility,
	InitSequence,

	PG_BuildMeshes,
	PG_BuildVisibility,

	COUNT
};
