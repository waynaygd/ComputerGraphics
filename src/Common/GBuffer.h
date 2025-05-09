#pragma once
#include "d3dUtil.h"

enum GBufferIndex {
	GBUFFER_DIFFUSE = 0,
	GBUFFER_NORMAL,
	GBUFFER_MATERIAL,
	GBUFFER_COUNT
};

struct GBufferTexture
{
	Microsoft::WRL::ComPtr<ID3D12Resource> TResource = nullptr;
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = {};
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = {};
	D3D12_RESOURCE_STATES prevState = D3D12_RESOURCE_STATE_COMMON;

	void reset()
	{
		TResource.Reset();
		rtvHandle.ptr = 0;
		srvHandle.ptr = 0;
	}
};


class GBuffer {
public:
	GBuffer(ID3D12Device* device, int width, int height);
	~GBuffer();

	void OnResize(ID3D12GraphicsCommandList* cmdList, int width, int height);
	void CreateGBT(int i, CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle, CD3DX12_CPU_DESCRIPTOR_HANDLE srvHeapHandle,
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHeapHandle);

private:
	int mWidth = 0;
	int mHeight = 0;

	UINT mRTVDescriptorSize;
	UINT mSRVDescriptorSize;
	UINT mDSVDescriptorSize;

	GBufferTexture mInfo[(int)GBufferIndex::GBUFFER_COUNT];

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRTVHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mSRVHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDSVHeap;

	Microsoft::WRL::ComPtr<ID3D12Device> mDevice;
};