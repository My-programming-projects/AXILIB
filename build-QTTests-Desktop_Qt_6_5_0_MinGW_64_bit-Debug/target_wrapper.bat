@echo off
SetLocal EnableDelayedExpansion
(set PATH=C:\Programy\Programowanie\Qt\6.5.0\mingw_64\bin;!PATH!)
if defined QT_PLUGIN_PATH (
    set QT_PLUGIN_PATH=C:\Programy\Programowanie\Qt\6.5.0\mingw_64\plugins;!QT_PLUGIN_PATH!
) else (
    set QT_PLUGIN_PATH=C:\Programy\Programowanie\Qt\6.5.0\mingw_64\plugins
)
%*
EndLocal
