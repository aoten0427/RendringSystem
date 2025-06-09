# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 重要な注意事項

**言語設定**: このプロジェクトのコメントや説明は**日本語**で記述してください。コードのコメント、変数名の説明、開発ドキュメントはすべて日本語で統一されています。

**C++バージョン**: このプロジェクトは**C++11標準**で動作するように設計されています。C++14以降の機能は使用しないでください。

## Build and Development Commands

### Building the Project
```bash
# Build in Visual Studio
# Open 3DPG.sln in Visual Studio and build using Ctrl+Shift+B
# Or use MSBuild from command line:
msbuild 3DPG.sln /p:Configuration=Debug /p:Platform=x64
```

### Dependencies
- DirectXTK Desktop 2019 (2024.1.1.1)
- Microsoft XAudio2 Redist (1.2.11)
- Windows 10 SDK
- Visual Studio 2019/2022 with v143 toolset

### Shader Compilation
Shaders are automatically compiled during build:
- HLSL files in `Base/Shaders/` and `Base/RenderingSystem/Shaders/`
- Output CSO files go to `Resources/Shaders/`

## Architecture Overview

This is a **DirectX 11-based 3D rendering system** with component-entity architecture, written in C++ with Japanese comments throughout the codebase.

### Core Systems

**Game Loop Structure:**
```
Main.cpp → Game.cpp → SceneManager → Scene → Objects → Components
```

**Key Architectural Patterns:**
- **Component-Entity System**: Objects contain multiple Components
- **Singleton Pattern**: GameResources, EventManager
- **Strategy Pattern**: IRenderingStrategy for rendering approaches
- **Observer Pattern**: Event system with ISubject/IObserver
- **Dependency Injection**: CommonResources passed to components

### Component System
- **Object**: Entity that holds Transform + other Components
- **Component**: Base class with lifecycle methods (Start, Update, Render, OnDestroy)
- **Transform**: Hierarchical position/rotation/scale (always present on Objects)
- **Model3D**: 3D model rendering with material assignment

Components are created via templates: `object->AddComponent<MyComponent>(args...)`

### Rendering Pipeline
1. **RenderingSystem** collects Model3D components
2. **MaterialManager** handles material lifecycle
3. **RenderDatas** batches objects by material/model
4. **IRenderingStrategy** executes rendering (currently StandardRenderStrategy)
5. Supports instanced rendering for multiple objects with same model/material

### Resource Management
- **GameResources** (singleton): Centralized loading of models, textures, shaders
- **JSON-driven**: Resource paths defined in `Resources/JSON/GameResources/`
- **Smart pointers**: extensive use of unique_ptr, shared_ptr, ComPtr
- **RAII**: DirectX resources managed via ComPtr

### Scene System
- **SceneManager**: Handles scene transitions and UnbreakableManager
- **Scene**: Base class with state machine (RESERVE→PLAY→STOP→FEAD→END)
- **UnbreakableManager**: Objects that persist across scene changes

### Event System
- **EventManager**: String-based event registration
- **ISubject/IObserver**: Decoupled communication
- **Deferred registration**: Can register observers before subjects exist

## Development Guidelines

### Adding New Components
1. Inherit from `Component` class
2. Override virtual methods: `Start()`, `Update()`, `Render()`, `OnDestroy()`
3. Use `m_commonResources` for accessing shared systems
4. Set `m_updateOrder` for execution priority

### Creating New Scenes
1. Inherit from `Scene` class  
2. Override `Start()` to add objects: `AddObject<MyObject>()`
3. Handle scene state transitions in `Update()`

### Material System
1. Implement `IMaterial` interface with `Bind()` and `Clean()` methods
2. Register with `MaterialFactory` for automatic creation
3. Store rendering constants in `RenderingConfig.h`

### Key Files for Development
- `Base/Base.h`: Main include header for the framework
- `Game.h`: Application entry point and main loop
- `Base/Scene/Scene.h`: Scene management base class
- `Base/Object/Object.h`: Entity system foundation
- `Base/Component/Component.h`: Component system base
- `Base/RenderingSystem/RenderingSystem.h`: Rendering pipeline core

### Japanese Language Support
- Many comments and some identifiers are in Japanese
- Uses Japanese fonts and ImGui Japanese glyph ranges
- String resources may contain Japanese text