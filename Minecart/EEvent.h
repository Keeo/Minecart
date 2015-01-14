#pragma once

enum EEvent {

	SetCameraPosRot,

	// Core events
	Shutdown,
		
	FetchCameraData,

	BuildMeshForChunk,
	BuildMeshBForChunk,

	// Chunk events
	eveChunkGet,
	eveChunkOnLoad,
	eveLoadNewChunk,

	// Delete cube
	eveDeleteCube,

	// When player move and changes chunk
	evePlayerChangedChunk,

	// Put position, view and projection matrix into shader
	eveCameraDrawWorld,
	eveCameraDrawWeather,
	eveCameraGetPositionPointer, // gets camera pointer to position glm::vec3

	getDirectionalLight, //gets directional light from daynight control

	// return block in provided position {get vec3,ret block}
	eveGetBlock,

	// this element has to be the last one, due to its use as a eventc counter
	COUNT
};
