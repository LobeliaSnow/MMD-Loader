#pragma once
namespace ML {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//					Information
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//private:
	__forceinline Information::Information() = default;
	__forceinline Information::~Information() = default;
	//public:
	__forceinline const std::string& Information::GetAPIName() { return apiName; }
	__forceinline std::string Information::GetAPIVersion() {
		std::stringstream _stream;
		_stream << mainVersion << "." << subVersion << type;
		return _stream.str();
	}
	__forceinline const std::string& Information::GetAPIComment() {
		static std::string comment = "����X�^�e�B�b�N���b�V��(�{�[������)�̂ݑΉ��A�{�[�����K�X�Ή�����B\n�Ƃ肠�����R�����g����̂��}���B\n";
		return comment;
	}
	__forceinline const int Information::GetAPIMainVersion() { return mainVersion; }
	__forceinline const int Information::GetAPISubVersion() { return subVersion; }
	__forceinline const std::string& Information::GetType() { return type; }

}