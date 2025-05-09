#include "GBuffer.h"

GBuffer::GBuffer(ID3D12Device* device, int width, int height)
{
	mDevice = device;
	mWidth = width;
	mHeight = height;

	mRTVDescriptorSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	mSRVDescriptorSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	mDSVDescriptorSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
}

GBuffer::~GBuffer()
{
	for (auto& texture : mInfo)
		texture.reset();
}

void GBuffer::OnResize(ID3D12GraphicsCommandList* cmdList, int width, int height)
{
	mWidth = width;
	mHeight = height;

	for (auto& texture : mInfo)
		texture.Reset();

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(mRTVHeap->GetCPUDescriptorHandleForHeapStart());
	CD3DX12_CPU_DESCRIPTOR_HANDLE srvHandle(mSRVHeap->GetCPUDescriptorHandleForHeapStart());
	CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(mDSVHeap->GetCPUDescriptorHandleForHeapStart());

	for (int i = 0; i < (int)GBufferIndex::GBUFFER_COUNT; i++)
	{
		CreateGBT(i, rtvHandle, srvHandle, dsvHandle);
		rtvHandle.Offset(1, _rtvDescriptorSize);
		if (i == (int)GBufferIndex::GBUFFER_DEPTH)
			dsvHandle.Offset(1, _dsvDescriptorSize);
		else
			srvHandle.Offset(1, _srvDescriptorSize);

	}
}

void GBuffer::CreateGBT(int i, CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle, CD3DX12_CPU_DESCRIPTOR_HANDLE srvHeapHandle, CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHeapHandle)
{
}
