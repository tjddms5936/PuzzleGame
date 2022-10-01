// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEGAME_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// ���������Լ� ����
	virtual void HostServer() = 0;
	/**
		���� virtual void Host(); �� �س����� ��ü���̶� �Լ��� �����ؾ� �� 
		�����ϰ� ��ӹ޴� Ŭ���������� �����ϰ� �ʹٸ� ���������Լ��� ������־�� ��.
		���������Լ��� ���Ͱ��� = 0 �� ���ָ� ��.
	*/

	virtual void Join(const FString& Address) = 0;

	virtual void CancelMenu() = 0;

	virtual void QuitMenu() = 0;

	virtual void ExitGameFunc() = 0;

	virtual bool CallBackBool(bool input) = 0;
};
