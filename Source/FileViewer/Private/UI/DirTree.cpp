// Fill out your copyright notice in the Description page of Project Settings.

#include "FileViewer.h"
#include "DirTree.h"
#include "SFileView.h"

#define LOCTEXT_NAMESPACE "FFileViewerModule"

#if WITH_EDITOR
const FText UDirTree::GetPaletteCategory()
{
	return LOCTEXT("FileViewer", "DirTree");
}

#endif

UDirTree::UDirTree(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UE_LOG(LogFileViewer, Log, TEXT("[UDirTree] UDirTree(): Construct"));
}

void UDirTree::NavParent()
{
	if (!MyFileView.IsValid()) return;

	MyFileView->Nav_Parent();
}

FText UDirTree::Get_ParentPath() const
{
	return FText::FromString(MyFileView->mstr_CurPath);
}

TSharedRef<SWidget> UDirTree::RebuildWidget()
{
	MyFileView = SNew(SFileView).ListDbClicked(BIND_UOBJECT_DELEGATE(FDbClickDelegate, DirTreeDbClick));
	MyFileView->Refresh_FileList(FPaths::GameDir());
	return MyFileView.ToSharedRef();
}

void UDirTree::DirTreeDbClick(const FString& InPath)
{
	UE_LOG(LogFileViewer, Log, TEXT("[UDirTree] DirTreeDbClick(): %s||%s"), *MyFileView->mstr_CurPath,*InPath);
	UGameplayStatics::OpenLevel(this, *InPath);
}

#undef LOCTEXT_NAMESPACE