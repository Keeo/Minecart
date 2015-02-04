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
	WatcherErase,
	WatcherChange,

	CameraChangedChunk,

	FillChunks,
	RebuildVisbility,
	InitSequence,
	GenerateAndMoveSlice,

	PG_BuildMeshes1d,
	PG_BuildMeshes2d,
	PG_BuildMeshesTCB,
	PG_BuildVisibility,

	LoadMeshFromThread,

	DisposeChunk,

	COUNT
};
