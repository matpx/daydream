const std = @import("std");

// fn source_pair_needs_update(infile_path: []const u8, outfile_path: []const u8) !bool {
//     const infile = try std.fs.cwd().openFile(infile_path, .{});
//     const outfile = std.fs.cwd().openFile(outfile_path, .{}) catch return true;

//     return (try infile.metadata()).accessed() > (try outfile.metadata()).accessed();
// }

const jolt_src_dir = "thirdparty/JoltPhysics/Jolt";

const jolt_src = &.{
    jolt_src_dir ++ "/AABBTree/AABBTreeBuilder.cpp",
    jolt_src_dir ++ "/Core/Color.cpp",
    jolt_src_dir ++ "/Core/Factory.cpp",
    jolt_src_dir ++ "/Core/IssueReporting.cpp",
    jolt_src_dir ++ "/Core/JobSystemSingleThreaded.cpp",
    jolt_src_dir ++ "/Core/JobSystemThreadPool.cpp",
    jolt_src_dir ++ "/Core/JobSystemWithBarrier.cpp",
    jolt_src_dir ++ "/Core/LinearCurve.cpp",
    jolt_src_dir ++ "/Core/Memory.cpp",
    jolt_src_dir ++ "/Core/Profiler.cpp",
    jolt_src_dir ++ "/Core/RTTI.cpp",
    jolt_src_dir ++ "/Core/Semaphore.cpp",
    jolt_src_dir ++ "/Core/StringTools.cpp",
    jolt_src_dir ++ "/Core/TickCounter.cpp",
    jolt_src_dir ++ "/Geometry/ConvexHullBuilder.cpp",
    jolt_src_dir ++ "/Geometry/ConvexHullBuilder2D.cpp",
    jolt_src_dir ++ "/Geometry/Indexify.cpp",
    jolt_src_dir ++ "/Geometry/OrientedBox.cpp",
    jolt_src_dir ++ "/Math/Vec3.cpp",
    jolt_src_dir ++ "/ObjectStream/ObjectStream.cpp",
    jolt_src_dir ++ "/ObjectStream/ObjectStreamBinaryIn.cpp",
    jolt_src_dir ++ "/ObjectStream/ObjectStreamBinaryOut.cpp",
    jolt_src_dir ++ "/ObjectStream/ObjectStreamIn.cpp",
    jolt_src_dir ++ "/ObjectStream/ObjectStreamOut.cpp",
    jolt_src_dir ++ "/ObjectStream/ObjectStreamTextIn.cpp",
    jolt_src_dir ++ "/ObjectStream/ObjectStreamTextOut.cpp",
    jolt_src_dir ++ "/ObjectStream/SerializableObject.cpp",
    jolt_src_dir ++ "/ObjectStream/TypeDeclarations.cpp",
    jolt_src_dir ++ "/Physics/Body/Body.cpp",
    jolt_src_dir ++ "/Physics/Body/BodyAccess.cpp",
    jolt_src_dir ++ "/Physics/Body/BodyCreationSettings.cpp",
    jolt_src_dir ++ "/Physics/Body/BodyInterface.cpp",
    jolt_src_dir ++ "/Physics/Body/BodyManager.cpp",
    jolt_src_dir ++ "/Physics/Body/MassProperties.cpp",
    jolt_src_dir ++ "/Physics/Body/MotionProperties.cpp",
    jolt_src_dir ++ "/Physics/Character/Character.cpp",
    jolt_src_dir ++ "/Physics/Character/CharacterBase.cpp",
    jolt_src_dir ++ "/Physics/Character/CharacterVirtual.cpp",
    jolt_src_dir ++ "/Physics/Collision/BroadPhase/BroadPhase.cpp",
    jolt_src_dir ++ "/Physics/Collision/BroadPhase/BroadPhaseBruteForce.cpp",
    jolt_src_dir ++ "/Physics/Collision/BroadPhase/BroadPhaseQuadTree.cpp",
    jolt_src_dir ++ "/Physics/Collision/BroadPhase/QuadTree.cpp",
    jolt_src_dir ++ "/Physics/Collision/CastConvexVsTriangles.cpp",
    jolt_src_dir ++ "/Physics/Collision/CastSphereVsTriangles.cpp",
    jolt_src_dir ++ "/Physics/Collision/CollideConvexVsTriangles.cpp",
    jolt_src_dir ++ "/Physics/Collision/CollideSphereVsTriangles.cpp",
    jolt_src_dir ++ "/Physics/Collision/CollisionDispatch.cpp",
    jolt_src_dir ++ "/Physics/Collision/CollisionGroup.cpp",
    jolt_src_dir ++ "/Physics/Collision/EstimateCollisionResponse.cpp",
    jolt_src_dir ++ "/Physics/Collision/GroupFilter.cpp",
    jolt_src_dir ++ "/Physics/Collision/GroupFilterTable.cpp",
    jolt_src_dir ++ "/Physics/Collision/ManifoldBetweenTwoFaces.cpp",
    jolt_src_dir ++ "/Physics/Collision/NarrowPhaseQuery.cpp",
    jolt_src_dir ++ "/Physics/Collision/NarrowPhaseStats.cpp",
    jolt_src_dir ++ "/Physics/Collision/PhysicsMaterial.cpp",
    jolt_src_dir ++ "/Physics/Collision/PhysicsMaterialSimple.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/BoxShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/CapsuleShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/CompoundShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/ConvexHullShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/ConvexShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/CylinderShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/DecoratedShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/HeightFieldShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/MeshShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/MutableCompoundShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/OffsetCenterOfMassShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/RotatedTranslatedShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/ScaledShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/Shape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/SphereShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/StaticCompoundShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/TaperedCapsuleShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/Shape/TriangleShape.cpp",
    jolt_src_dir ++ "/Physics/Collision/TransformedShape.cpp",
    jolt_src_dir ++ "/Physics/Constraints/ConeConstraint.cpp",
    jolt_src_dir ++ "/Physics/Constraints/Constraint.cpp",
    jolt_src_dir ++ "/Physics/Constraints/ConstraintManager.cpp",
    jolt_src_dir ++ "/Physics/Constraints/ContactConstraintManager.cpp",
    jolt_src_dir ++ "/Physics/Constraints/DistanceConstraint.cpp",
    jolt_src_dir ++ "/Physics/Constraints/FixedConstraint.cpp",
    jolt_src_dir ++ "/Physics/Constraints/GearConstraint.cpp",
    jolt_src_dir ++ "/Physics/Constraints/HingeConstraint.cpp",
    jolt_src_dir ++ "/Physics/Constraints/MotorSettings.cpp",
    jolt_src_dir ++ "/Physics/Constraints/PathConstraint.cpp",
    jolt_src_dir ++ "/Physics/Constraints/PathConstraintPath.cpp",
    jolt_src_dir ++ "/Physics/Constraints/PathConstraintPathHermite.cpp",
    jolt_src_dir ++ "/Physics/Constraints/PointConstraint.cpp",
    jolt_src_dir ++ "/Physics/Constraints/PulleyConstraint.cpp",
    jolt_src_dir ++ "/Physics/Constraints/RackAndPinionConstraint.cpp",
    jolt_src_dir ++ "/Physics/Constraints/SixDOFConstraint.cpp",
    jolt_src_dir ++ "/Physics/Constraints/SliderConstraint.cpp",
    jolt_src_dir ++ "/Physics/Constraints/SpringSettings.cpp",
    jolt_src_dir ++ "/Physics/Constraints/SwingTwistConstraint.cpp",
    jolt_src_dir ++ "/Physics/Constraints/TwoBodyConstraint.cpp",
    jolt_src_dir ++ "/Physics/DeterminismLog.cpp",
    jolt_src_dir ++ "/Physics/IslandBuilder.cpp",
    jolt_src_dir ++ "/Physics/LargeIslandSplitter.cpp",
    jolt_src_dir ++ "/Physics/PhysicsLock.cpp",
    jolt_src_dir ++ "/Physics/PhysicsScene.cpp",
    jolt_src_dir ++ "/Physics/PhysicsSystem.cpp",
    jolt_src_dir ++ "/Physics/PhysicsUpdateContext.cpp",
    jolt_src_dir ++ "/Physics/Ragdoll/Ragdoll.cpp",
    jolt_src_dir ++ "/Physics/SoftBody/SoftBodyCreationSettings.cpp",
    jolt_src_dir ++ "/Physics/SoftBody/SoftBodyMotionProperties.cpp",
    jolt_src_dir ++ "/Physics/SoftBody/SoftBodyShape.cpp",
    jolt_src_dir ++ "/Physics/SoftBody/SoftBodySharedSettings.cpp",
    jolt_src_dir ++ "/Physics/StateRecorderImpl.cpp",
    jolt_src_dir ++ "/Physics/Vehicle/MotorcycleController.cpp",
    jolt_src_dir ++ "/Physics/Vehicle/TrackedVehicleController.cpp",
    jolt_src_dir ++ "/Physics/Vehicle/VehicleAntiRollBar.cpp",
    jolt_src_dir ++ "/Physics/Vehicle/VehicleCollisionTester.cpp",
    jolt_src_dir ++ "/Physics/Vehicle/VehicleConstraint.cpp",
    jolt_src_dir ++ "/Physics/Vehicle/VehicleController.cpp",
    jolt_src_dir ++ "/Physics/Vehicle/VehicleDifferential.cpp",
    jolt_src_dir ++ "/Physics/Vehicle/VehicleEngine.cpp",
    jolt_src_dir ++ "/Physics/Vehicle/VehicleTrack.cpp",
    jolt_src_dir ++ "/Physics/Vehicle/VehicleTransmission.cpp",
    jolt_src_dir ++ "/Physics/Vehicle/Wheel.cpp",
    jolt_src_dir ++ "/Physics/Vehicle/WheeledVehicleController.cpp",
    jolt_src_dir ++ "/RegisterTypes.cpp",
    jolt_src_dir ++ "/Renderer/DebugRenderer.cpp",
    jolt_src_dir ++ "/Renderer/DebugRendererPlayback.cpp",
    jolt_src_dir ++ "/Renderer/DebugRendererRecorder.cpp",
    jolt_src_dir ++ "/Skeleton/SkeletalAnimation.cpp",
    jolt_src_dir ++ "/Skeleton/Skeleton.cpp",
    jolt_src_dir ++ "/Skeleton/SkeletonMapper.cpp",
    jolt_src_dir ++ "/Skeleton/SkeletonPose.cpp",
    jolt_src_dir ++ "/TriangleGrouper/TriangleGrouperClosestCentroid.cpp",
    jolt_src_dir ++ "/TriangleGrouper/TriangleGrouperMorton.cpp",
    jolt_src_dir ++ "/TriangleSplitter/TriangleSplitter.cpp",
    jolt_src_dir ++ "/TriangleSplitter/TriangleSplitterBinning.cpp",
    jolt_src_dir ++ "/TriangleSplitter/TriangleSplitterFixedLeafSize.cpp",
    jolt_src_dir ++ "/TriangleSplitter/TriangleSplitterLongestAxis.cpp",
    jolt_src_dir ++ "/TriangleSplitter/TriangleSplitterMean.cpp",
    jolt_src_dir ++ "/TriangleSplitter/TriangleSplitterMorton.cpp",
};

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "daydream",
        .target = target,
        .optimize = optimize,
    });

    {
        const system_include_paths: []const []const u8 = &.{
            "thirdparty/SDL2/x86_64-w64-mingw32/include/",
            "thirdparty/nvrhi/include",
            "thirdparty/JoltPhysics/",
            "thirdparty/sokol/",
            "thirdparty/glm/",
            "thirdparty/entt/src/",
            "thirdparty/fmt/include/",
            "thirdparty/GSL/include/",
            "thirdparty/expected/include/",
            "thirdparty/cgltf/",
        };

        for (system_include_paths) |include_path| {
            exe.addSystemIncludePath(std.Build.LazyPath{ .path = include_path });
        }
    }

    {
        const compiler_args_common: []const []const u8 = &.{
            "-std=c++20",
            // "-fno-exceptions",
            // "-fno-rtti",
            "-Werror",
            "-Weverything",
            "-Wno-missing-prototypes",
            "-Wno-c++98-compat-pedantic",
            "-Wno-c++98-compat",
            "-Wno-padded",
            "-fstrict-flex-arrays=3",
            "-fPIE",
        };

        const compiler_args: []const []const u8 =
            if (optimize == std.builtin.OptimizeMode.Debug)
            compiler_args_common ++ .{ "-D_LIBCPP_ENABLE_DEBUG_MODE", "-D_GLIBCXX_DEBUG" }
        else if (optimize == std.builtin.OptimizeMode.ReleaseSafe)
            compiler_args_common ++ .{
                "-D_LIBCPP_ENABLE_ASSERTIONS",
                "-D_GLIBCXX_ASSERTIONS",
                "-fcf-protection=full",
                "-Wa,--noexecstack",
                "-ftrivial-auto-var-init=zero",
                // "-fstack-clash-protection",
            }
        else
            compiler_args_common;

        const source_files: []const []const u8 = &.{
            "src/main.cpp",
            "src/impl.cpp",
            "src/app.cpp",
            "src/window.cpp",
            "src/renderer.cpp",
            "src/loader.cpp",
        };

        exe.addCSourceFiles(
            source_files,
            compiler_args,
        );
    }

    {
        const source_files: []const []const u8 = &.{
            "thirdparty/nvrhi/src/common/dxgi-format.cpp",
            "thirdparty/nvrhi/src/common/format-info.cpp",
            "thirdparty/nvrhi/src/common/misc.cpp",
            "thirdparty/nvrhi/src/common/sparse-bitset.cpp",
            "thirdparty/nvrhi/src/common/state-tracking.cpp",
            "thirdparty/nvrhi/src/common/utils.cpp",
            "thirdparty/nvrhi/src/d3d11/d3d11-buffer.cpp",
            "thirdparty/nvrhi/src/d3d11/d3d11-commandlist.cpp",
            "thirdparty/nvrhi/src/d3d11/d3d11-compute.cpp",
            "thirdparty/nvrhi/src/d3d11/d3d11-constants.cpp",
            "thirdparty/nvrhi/src/d3d11/d3d11-device.cpp",
            "thirdparty/nvrhi/src/d3d11/d3d11-graphics.cpp",
            "thirdparty/nvrhi/src/d3d11/d3d11-queries.cpp",
            "thirdparty/nvrhi/src/d3d11/d3d11-resource-bindings.cpp",
            "thirdparty/nvrhi/src/d3d11/d3d11-shader.cpp",
            "thirdparty/nvrhi/src/d3d11/d3d11-texture.cpp",
            "thirdparty/nvrhi/src/validation/validation-commandlist.cpp",
            "thirdparty/nvrhi/src/validation/validation-device.cpp",
        };

        const nvrhi = b.addStaticLibrary(.{
            .name = "nvrhi",
            .target = target,
            .optimize = optimize,
        });

        const compiler_args: []const []const u8 = &.{};

        nvrhi.addCSourceFiles(source_files, compiler_args);
        nvrhi.addIncludePath(std.Build.LazyPath{ .path = "thirdparty/nvrhi/include" });
        nvrhi.linkLibC();
        nvrhi.linkLibCpp();
        exe.linkLibrary(nvrhi);

        exe.step.dependOn(&b.addSystemCommand(&.{ "toolchain/ShaderMake/ShaderMake.exe", "-p", "DXBC", "--header", "-c", "shader/shadermake.cfg", "--compiler", "toolchain/ShaderMake/fxc.exe", "-o", "toolchain-out/shader/" }).step);
    }

    {
        const jolt = b.addStaticLibrary(.{
            .name = "jolt",
            .target = target,
            .optimize = optimize,
        });

        const compiler_args: []const []const u8 = &.{
            // "-DJPH_PROFILE_ENABLED",
            // "-DJPH_EXTERNAL_PROFILE",
            // "-DJPH_DEBUG_RENDERER",
            // "-DJPH_DISABLE_TEMP_ALLOCATOR",
            // "-DJPH_DISABLE_CUSTOM_ALLOCATOR",
            // "-DJPH_FLOATING_POINT_EXCEPTIONS_ENABLED",
            // "-DJPH_CROSS_PLATFORM_DETERMINISTIC",
            // "-DJPH_DOUBLE_PRECISION",
            // "-DJPH_USE_SSE4_1",
            // "-DJPH_USE_SSE4_2",
            // "-DJPH_USE_F16C",
            // "-DJPH_USE_LZCNT",
            // "-DJPH_USE_TZCNT",
            // "-DJPH_USE_AVX",
            // "-DJPH_USE_AVX2",
            // "-DJPH_USE_AVX512",
            // "-DJPH_USE_FMADD",
        };

        jolt.addCSourceFiles(jolt_src, compiler_args);
        jolt.addIncludePath(std.Build.LazyPath{ .path = "thirdparty/JoltPhysics/" });
        jolt.linkLibC();
        jolt.linkLibCpp();
        exe.linkLibrary(jolt);
    }

    {
        const system_libs: []const []const u8 = if (exe.target.isWindows())
            &.{
                "gdi32",
                "ole32",
                "setupapi",
                "winmm",
                "imm32",
                "oleaut32",
                "version",
                "d3d11",
            }
        else
            &.{};

        for (system_libs) |lib| {
            exe.linkSystemLibrary(lib);
        }
    }

    {
        exe.addObjectFile(std.Build.LazyPath{ .path = "thirdparty/SDL2/x86_64-w64-mingw32/lib/libSDL2.a" });
        // exe.addObjectFile(std.Build.LazyPath{ .path = "thirdparty/SDL2/x86_64-w64-mingw32/lib/libSDL2.dll.a" });
        exe.addObjectFile(std.Build.LazyPath{ .path = "thirdparty/SDL2/x86_64-w64-mingw32/lib/libSDL2main.a" });
        // b.installBinFile("thirdparty/SDL2/x86_64-w64-mingw32/bin/SDL2.dll", "SDL2.dll");
    }

    // {
    //     const shaderc: []const u8 = if (exe.target.isWindows())
    //         "toolchain/sokol-tools-bin/bin/win32/sokol-shdc.exe"
    //     else
    //         "toolchain/sokol-tools-bin/bin/linux/sokol-shdc";

    //     const shaders: []const []const u8 = &.{
    //         "unlit",
    //     };

    //     const shader_indir = "shader/";
    //     const shader_outdir = "shader/include/shader/";

    //     for (shaders) |shader| {
    //         var infile_buffer = [_]u8{undefined} ** 256;
    //         var outfile_buffer = [_]u8{undefined} ** 256;

    //         const infile_path = try std.fmt.bufPrint(&infile_buffer, shader_indir ++ "{s}.glsl", .{shader});
    //         const outfile_path = try std.fmt.bufPrint(&outfile_buffer, shader_outdir ++ "{s}.h", .{shader});

    //         if (try source_pair_needs_update(infile_path, outfile_path)) {
    //             const infile_arg = try std.fmt.bufPrint(&infile_buffer, "--input=" ++ shader_indir ++ "{s}.glsl", .{shader});
    //             const outfile_arg = try std.fmt.bufPrint(&outfile_buffer, "--output=" ++ shader_outdir ++ "{s}.h", .{shader});

    //             exe.step.dependOn(&b.addSystemCommand(&.{ shaderc, infile_arg, outfile_arg, "--slang=glsl330" }).step);
    //         }
    //     }
    // }

    exe.linkLibC();
    exe.linkLibCpp();
    exe.pie = true;
    exe.link_z_relro = true;
    // exe.want_lto = false; // https://github.com/ziglang/zig/issues/15958

    b.installArtifact(exe);
}
