
#include "Interface.h"
#include "GameObject.h"

using namespace hm;

namespace yj
{
	class TextBox :
		public Interface
	{
	public:

		TextBox();
		virtual ~TextBox();

		TextBox* Clone()
		{
			TextBox* _pTextBox = GameObject::Clone<TextBox>();
			return _pTextBox;
		}
	};
}