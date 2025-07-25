/// <summary>
/// �X�R�A���|�b�v������^�C�~���O�ƐF��`����N���X
/// </summary>
#pragma once

class PopScoreManager :public IGameObject
{
public:
	/// <summary>
	/// ���̃N���X��true�ɂ��āA�X�R�A���|�b�v�����鍇�}���o���܂��B
	/// </summary>
	/// <param name="a">�ݒ肷��t���O�̒l�itrue �܂��� false�j�B</param>
	const void SetPopFlag(bool a)
	{
		isPopFlag = a;
	}

	/// <summary>
	/// Star�N���X����A���ł����X�^�[�̐F���擾���܂��B
	/// </summary>
	/// <returns>colorChecker �̌��݂̒l��Ԃ��܂��B</returns>
	const int GetColorChecker()
	{
		return colorChecker;
	}

	/// <summary>
	/// �X�^�[�N���X������ł����X�^�[�̐F���󂯎��܂��B
	/// </summary>
	/// <param name="a">�ݒ肷�� colorChecker �̒l�B</param>
	const void SetColorChecker(int a)
	{
		colorChecker = a;
	}

private:
	void Update()override final;

	bool isPopFlag = false;	// �X�R�A���|�b�v������t���O���i�[���܂��B
	int colorChecker = 0;	// ���ł����X�^�[�̐F���i�[���APopScore�N���X�ɓn���܂��B
};

