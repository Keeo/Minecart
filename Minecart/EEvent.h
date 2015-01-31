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

	PG_BuildMeshes1d,
	PG_BuildMeshes2d,
	PG_BuildVisibility,

	LoadMeshFromThread,

	DisposeChunk,

	COUNT
};
