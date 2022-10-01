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
	// 순수가상함수 생성
	virtual void HostServer() = 0;
	/**
		만약 virtual void Host(); 만 해놓으면 몸체만이라도 함수를 구현해야 함 
		완전하게 상속받는 클래스에서만 구현하고 싶다면 순수가상함수로 만들어주어야 함.
		순수가상함수는 위와같이 = 0 을 해주면 됨.
	*/

	virtual void Join(const FString& Address) = 0;

	virtual void CancelMenu() = 0;

	virtual void QuitMenu() = 0;

	virtual void ExitGameFunc() = 0;

	virtual bool CallBackBool(bool input) = 0;
};
