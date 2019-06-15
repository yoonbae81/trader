#include "pch.h"
#include "AssetManager.h"

AssetManager::AssetManager(double cash)
{
	send(cash_, cash);
}

double AssetManager::cash()
{
	return receive(cash_);
}

void AssetManager::run()
{
	done();
}
