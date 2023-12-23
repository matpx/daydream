const std = @import("std");

const jolt_sources_dir = "thirdparty/JoltPhysics/Jolt/";

const jolt_source_files = &.{
    jolt_sources_dir ++ "AABBTree/AABBTreeBuilder.cpp",
    jolt_sources_dir ++ "Core/Color.cpp",
    jolt_sources_dir ++ "Core/Factory.cpp",
    jolt_sources_dir ++ "Core/IssueReporting.cpp",
    jolt_sources_dir ++ "Core/JobSystemSingleThreaded.cpp",
    jolt_sources_dir ++ "Core/JobSystemThreadPool.cpp",
    jolt_sources_dir ++ "Core/JobSystemWithBarrier.cpp",
    jolt_sources_dir ++ "Core/LinearCurve.cpp",
    jolt_sources_dir ++ "Core/Memory.cpp",
    jolt_sources_dir ++ "Core/Profiler.cpp",
    jolt_sources_dir ++ "Core/RTTI.cpp",
    jolt_sources_dir ++ "Core/Semaphore.cpp",
    jolt_sources_dir ++ "Core/StringTools.cpp",
    jolt_sources_dir ++ "Core/TickCounter.cpp",
    jolt_sources_dir ++ "Geometry/ConvexHullBuilder.cpp",
    jolt_sources_dir ++ "Geometry/ConvexHullBuilder2D.cpp",
    jolt_sources_dir ++ "Geometry/Indexify.cpp",
    jolt_sources_dir ++ "Geometry/OrientedBox.cpp",
    jolt_sources_dir ++ "Math/Vec3.cpp",
    jolt_sources_dir ++ "ObjectStream/ObjectStream.cpp",
    jolt_sources_dir ++ "ObjectStream/ObjectStreamBinaryIn.cpp",
    jolt_sources_dir ++ "ObjectStream/ObjectStreamBinaryOut.cpp",
    jolt_sources_dir ++ "ObjectStream/ObjectStreamIn.cpp",
    jolt_sources_dir ++ "ObjectStream/ObjectStreamOut.cpp",
    jolt_sources_dir ++ "ObjectStream/ObjectStreamTextIn.cpp",
    jolt_sources_dir ++ "ObjectStream/ObjectStreamTextOut.cpp",
    jolt_sources_dir ++ "ObjectStream/SerializableObject.cpp",
    jolt_sources_dir ++ "ObjectStream/TypeDeclarations.cpp",
    jolt_sources_dir ++ "Physics/Body/Body.cpp",
    jolt_sources_dir ++ "Physics/Body/BodyAccess.cpp",
    jolt_sources_dir ++ "Physics/Body/BodyCreationSettings.cpp",
    jolt_sources_dir ++ "Physics/Body/BodyInterface.cpp",
    jolt_sources_dir ++ "Physics/Body/BodyManager.cpp",
    jolt_sources_dir ++ "Physics/Body/MassProperties.cpp",
    jolt_sources_dir ++ "Physics/Body/MotionProperties.cpp",
    jolt_sources_dir ++ "Physics/Character/Character.cpp",
    jolt_sources_dir ++ "Physics/Character/CharacterBase.cpp",
    jolt_sources_dir ++ "Physics/Character/CharacterVirtual.cpp",
    jolt_sources_dir ++ "Physics/Collision/BroadPhase/BroadPhase.cpp",
    jolt_sources_dir ++ "Physics/Collision/BroadPhase/BroadPhaseBruteForce.cpp",
    jolt_sources_dir ++ "Physics/Collision/BroadPhase/BroadPhaseQuadTree.cpp",
    jolt_sources_dir ++ "Physics/Collision/BroadPhase/QuadTree.cpp",
    jolt_sources_dir ++ "Physics/Collision/CastConvexVsTriangles.cpp",
    jolt_sources_dir ++ "Physics/Collision/CastSphereVsTriangles.cpp",
    jolt_sources_dir ++ "Physics/Collision/CollideConvexVsTriangles.cpp",
    jolt_sources_dir ++ "Physics/Collision/CollideSphereVsTriangles.cpp",
    jolt_sources_dir ++ "Physics/Collision/CollisionDispatch.cpp",
    jolt_sources_dir ++ "Physics/Collision/CollisionGroup.cpp",
    jolt_sources_dir ++ "Physics/Collision/EstimateCollisionResponse.cpp",
    jolt_sources_dir ++ "Physics/Collision/GroupFilter.cpp",
    jolt_sources_dir ++ "Physics/Collision/GroupFilterTable.cpp",
    jolt_sources_dir ++ "Physics/Collision/ManifoldBetweenTwoFaces.cpp",
    jolt_sources_dir ++ "Physics/Collision/NarrowPhaseQuery.cpp",
    jolt_sources_dir ++ "Physics/Collision/NarrowPhaseStats.cpp",
    jolt_sources_dir ++ "Physics/Collision/PhysicsMaterial.cpp",
    jolt_sources_dir ++ "Physics/Collision/PhysicsMaterialSimple.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/BoxShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/CapsuleShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/CompoundShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/ConvexHullShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/ConvexShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/CylinderShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/DecoratedShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/HeightFieldShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/MeshShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/MutableCompoundShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/OffsetCenterOfMassShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/RotatedTranslatedShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/ScaledShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/Shape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/SphereShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/StaticCompoundShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/TaperedCapsuleShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/Shape/TriangleShape.cpp",
    jolt_sources_dir ++ "Physics/Collision/TransformedShape.cpp",
    jolt_sources_dir ++ "Physics/Constraints/ConeConstraint.cpp",
    jolt_sources_dir ++ "Physics/Constraints/Constraint.cpp",
    jolt_sources_dir ++ "Physics/Constraints/ConstraintManager.cpp",
    jolt_sources_dir ++ "Physics/Constraints/ContactConstraintManager.cpp",
    jolt_sources_dir ++ "Physics/Constraints/DistanceConstraint.cpp",
    jolt_sources_dir ++ "Physics/Constraints/FixedConstraint.cpp",
    jolt_sources_dir ++ "Physics/Constraints/GearConstraint.cpp",
    jolt_sources_dir ++ "Physics/Constraints/HingeConstraint.cpp",
    jolt_sources_dir ++ "Physics/Constraints/MotorSettings.cpp",
    jolt_sources_dir ++ "Physics/Constraints/PathConstraint.cpp",
    jolt_sources_dir ++ "Physics/Constraints/PathConstraintPath.cpp",
    jolt_sources_dir ++ "Physics/Constraints/PathConstraintPathHermite.cpp",
    jolt_sources_dir ++ "Physics/Constraints/PointConstraint.cpp",
    jolt_sources_dir ++ "Physics/Constraints/PulleyConstraint.cpp",
    jolt_sources_dir ++ "Physics/Constraints/RackAndPinionConstraint.cpp",
    jolt_sources_dir ++ "Physics/Constraints/SixDOFConstraint.cpp",
    jolt_sources_dir ++ "Physics/Constraints/SliderConstraint.cpp",
    jolt_sources_dir ++ "Physics/Constraints/SpringSettings.cpp",
    jolt_sources_dir ++ "Physics/Constraints/SwingTwistConstraint.cpp",
    jolt_sources_dir ++ "Physics/Constraints/TwoBodyConstraint.cpp",
    jolt_sources_dir ++ "Physics/DeterminismLog.cpp",
    jolt_sources_dir ++ "Physics/IslandBuilder.cpp",
    jolt_sources_dir ++ "Physics/LargeIslandSplitter.cpp",
    jolt_sources_dir ++ "Physics/PhysicsLock.cpp",
    jolt_sources_dir ++ "Physics/PhysicsScene.cpp",
    jolt_sources_dir ++ "Physics/PhysicsSystem.cpp",
    jolt_sources_dir ++ "Physics/PhysicsUpdateContext.cpp",
    jolt_sources_dir ++ "Physics/Ragdoll/Ragdoll.cpp",
    jolt_sources_dir ++ "Physics/SoftBody/SoftBodyCreationSettings.cpp",
    jolt_sources_dir ++ "Physics/SoftBody/SoftBodyMotionProperties.cpp",
    jolt_sources_dir ++ "Physics/SoftBody/SoftBodyShape.cpp",
    jolt_sources_dir ++ "Physics/SoftBody/SoftBodySharedSettings.cpp",
    jolt_sources_dir ++ "Physics/StateRecorderImpl.cpp",
    jolt_sources_dir ++ "Physics/Vehicle/MotorcycleController.cpp",
    jolt_sources_dir ++ "Physics/Vehicle/TrackedVehicleController.cpp",
    jolt_sources_dir ++ "Physics/Vehicle/VehicleAntiRollBar.cpp",
    jolt_sources_dir ++ "Physics/Vehicle/VehicleCollisionTester.cpp",
    jolt_sources_dir ++ "Physics/Vehicle/VehicleConstraint.cpp",
    jolt_sources_dir ++ "Physics/Vehicle/VehicleController.cpp",
    jolt_sources_dir ++ "Physics/Vehicle/VehicleDifferential.cpp",
    jolt_sources_dir ++ "Physics/Vehicle/VehicleEngine.cpp",
    jolt_sources_dir ++ "Physics/Vehicle/VehicleTrack.cpp",
    jolt_sources_dir ++ "Physics/Vehicle/VehicleTransmission.cpp",
    jolt_sources_dir ++ "Physics/Vehicle/Wheel.cpp",
    jolt_sources_dir ++ "Physics/Vehicle/WheeledVehicleController.cpp",
    jolt_sources_dir ++ "RegisterTypes.cpp",
    jolt_sources_dir ++ "Renderer/DebugRenderer.cpp",
    jolt_sources_dir ++ "Renderer/DebugRendererPlayback.cpp",
    jolt_sources_dir ++ "Renderer/DebugRendererRecorder.cpp",
    jolt_sources_dir ++ "Skeleton/SkeletalAnimation.cpp",
    jolt_sources_dir ++ "Skeleton/Skeleton.cpp",
    jolt_sources_dir ++ "Skeleton/SkeletonMapper.cpp",
    jolt_sources_dir ++ "Skeleton/SkeletonPose.cpp",
    jolt_sources_dir ++ "TriangleGrouper/TriangleGrouperClosestCentroid.cpp",
    jolt_sources_dir ++ "TriangleGrouper/TriangleGrouperMorton.cpp",
    jolt_sources_dir ++ "TriangleSplitter/TriangleSplitter.cpp",
    jolt_sources_dir ++ "TriangleSplitter/TriangleSplitterBinning.cpp",
    jolt_sources_dir ++ "TriangleSplitter/TriangleSplitterFixedLeafSize.cpp",
    jolt_sources_dir ++ "TriangleSplitter/TriangleSplitterLongestAxis.cpp",
    jolt_sources_dir ++ "TriangleSplitter/TriangleSplitterMean.cpp",
    jolt_sources_dir ++ "TriangleSplitter/TriangleSplitterMorton.cpp",
};

pub fn package(
    allocator: std.mem.Allocator,
    compiler_args_global: []const []const u8,
    b: *std.Build,
    target: std.zig.CrossTarget,
    optimize: std.builtin.Mode,
) !*std.Build.CompileStep {
    const jolt = b.addStaticLibrary(.{
        .name = "jolt",
        .target = target,
        .optimize = optimize,
    });

    // const compiler_args: []const []const u8 = &.{
    //     // "-DJPH_PROFILE_ENABLED",
    //     // "-DJPH_EXTERNAL_PROFILE",
    //     // "-DJPH_DEBUG_RENDERER",
    //     // "-DJPH_DISABLE_TEMP_ALLOCATOR",
    //     // "-DJPH_DISABLE_CUSTOM_ALLOCATOR",
    //     // "-DJPH_FLOATING_POINT_EXCEPTIONS_ENABLED",
    //     // "-DJPH_CROSS_PLATFORM_DETERMINISTIC",
    //     // "-DJPH_DOUBLE_PRECISION",
    //     // "-DJPH_USE_SSE4_1",
    //     // "-DJPH_USE_SSE4_2",
    //     // "-DJPH_USE_F16C",
    //     // "-DJPH_USE_LZCNT",
    //     // "-DJPH_USE_TZCNT",
    //     // "-DJPH_USE_AVX",
    //     // "-DJPH_USE_AVX2",
    //     // "-DJPH_USE_AVX512",
    //     // "-DJPH_USE_FMADD",
    // };

    var compiler_args = std.ArrayList([]const u8).init(allocator);
    try compiler_args.appendSlice(compiler_args_global);

    jolt.addCSourceFiles(jolt_source_files, compiler_args.items);
    jolt.addIncludePath(std.Build.LazyPath{ .path = "thirdparty/JoltPhysics/" });
    jolt.linkLibCpp();
    return jolt;
}
