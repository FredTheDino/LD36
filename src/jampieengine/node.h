#pragma once

namespace Jam
{

	class Node
	{
	public:

		virtual void update(double delta) = 0;

		virtual void _rootEnter() = 0;
		virtual void _rootExit() = 0;
	};
}