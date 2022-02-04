; ModuleID = 'C:/Users/up201700488/feup-che/che-vitis/solution1/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%struct.BestPoint_SoA = type { [20 x i8], [20 x double] }
%struct.Known_Points_SoA = type { [186448 x double], [4336 x i8] }

; Function Attrs: noinline
define i8 @apatb_classifyinstance_ir(double* %new_point_features, i8 %new_point_classification_id, %struct.BestPoint_SoA* %best_points, i32 %num_classes, %struct.Known_Points_SoA* %known_points_soa, i32 %num_points, i32 %num_features) local_unnamed_addr #0 {
entry:
  %new_point_features_copy = alloca double, align 512
  %best_points_copy = alloca %struct.BestPoint_SoA, align 512
  %malloccall = tail call i8* @malloc(i64 1495920)
  %known_points_soa_copy = bitcast i8* %malloccall to %struct.Known_Points_SoA*
  call fastcc void @copy_in(double* %new_point_features, double* nonnull align 512 %new_point_features_copy, %struct.BestPoint_SoA* %best_points, %struct.BestPoint_SoA* nonnull align 512 %best_points_copy, %struct.Known_Points_SoA* %known_points_soa, %struct.Known_Points_SoA* %known_points_soa_copy)
  %0 = call i8 @apatb_classifyinstance_hw(double* %new_point_features_copy, i8 %new_point_classification_id, %struct.BestPoint_SoA* %best_points_copy, i32 %num_classes, %struct.Known_Points_SoA* %known_points_soa_copy, i32 %num_points, i32 %num_features)
  call fastcc void @copy_out(double* %new_point_features, double* nonnull align 512 %new_point_features_copy, %struct.BestPoint_SoA* %best_points, %struct.BestPoint_SoA* nonnull align 512 %best_points_copy, %struct.Known_Points_SoA* %known_points_soa, %struct.Known_Points_SoA* %known_points_soa_copy)
  tail call void @free(i8* %malloccall)
  ret i8 %0
}

declare noalias i8* @malloc(i64) local_unnamed_addr

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_in(double* readonly, double* noalias align 512, %struct.BestPoint_SoA* readonly, %struct.BestPoint_SoA* noalias align 512, %struct.Known_Points_SoA* readonly, %struct.Known_Points_SoA* noalias) unnamed_addr #1 {
entry:
  call fastcc void @onebyonecpy_hls.p0f64(double* align 512 %1, double* %0)
  call fastcc void @onebyonecpy_hls.p0struct.BestPoint_SoA(%struct.BestPoint_SoA* align 512 %3, %struct.BestPoint_SoA* %2)
  call fastcc void @onebyonecpy_hls.p0struct.Known_Points_SoA(%struct.Known_Points_SoA* %5, %struct.Known_Points_SoA* %4)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @onebyonecpy_hls.p0f64(double* noalias align 512, double* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq double* %0, null
  %3 = icmp eq double* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  %5 = bitcast double* %0 to i8*
  %6 = bitcast double* %1 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %5, i8* align 1 %6, i64 8, i1 false)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i1) #3

; Function Attrs: argmemonly noinline
define internal fastcc void @onebyonecpy_hls.p0struct.BestPoint_SoA(%struct.BestPoint_SoA* noalias align 512, %struct.BestPoint_SoA* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq %struct.BestPoint_SoA* %0, null
  %3 = icmp eq %struct.BestPoint_SoA* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx16 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr11 = getelementptr %struct.BestPoint_SoA, %struct.BestPoint_SoA* %0, i32 0, i32 0, i64 %for.loop.idx16
  %src.addr12 = getelementptr %struct.BestPoint_SoA, %struct.BestPoint_SoA* %1, i32 0, i32 0, i64 %for.loop.idx16
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %dst.addr11, i8* align 1 %src.addr12, i64 1, i1 false)
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx16, 1
  %exitcond17 = icmp ne i64 %for.loop.idx.next, 20
  br i1 %exitcond17, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop
  br label %for.loop4

for.loop4:                                        ; preds = %for.loop4, %copy.split
  %for.loop.idx515 = phi i64 [ 0, %copy.split ], [ %for.loop.idx5.next, %for.loop4 ]
  %dst.addr79.gep13 = getelementptr %struct.BestPoint_SoA, %struct.BestPoint_SoA* %0, i32 0, i32 1, i64 %for.loop.idx515
  %5 = bitcast double* %dst.addr79.gep13 to i8*
  %src.addr810.gep14 = getelementptr %struct.BestPoint_SoA, %struct.BestPoint_SoA* %1, i32 0, i32 1, i64 %for.loop.idx515
  %6 = bitcast double* %src.addr810.gep14 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %5, i8* align 1 %6, i64 8, i1 false)
  %for.loop.idx5.next = add nuw nsw i64 %for.loop.idx515, 1
  %exitcond = icmp ne i64 %for.loop.idx5.next, 20
  br i1 %exitcond, label %for.loop4, label %ret

ret:                                              ; preds = %for.loop4, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @onebyonecpy_hls.p0struct.Known_Points_SoA(%struct.Known_Points_SoA* noalias, %struct.Known_Points_SoA* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq %struct.Known_Points_SoA* %0, null
  %3 = icmp eq %struct.Known_Points_SoA* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx16 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr11.gep13 = getelementptr %struct.Known_Points_SoA, %struct.Known_Points_SoA* %0, i32 0, i32 0, i64 %for.loop.idx16
  %5 = bitcast double* %dst.addr11.gep13 to i8*
  %src.addr12.gep14 = getelementptr %struct.Known_Points_SoA, %struct.Known_Points_SoA* %1, i32 0, i32 0, i64 %for.loop.idx16
  %6 = bitcast double* %src.addr12.gep14 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %5, i8* align 1 %6, i64 8, i1 false)
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx16, 1
  %exitcond17 = icmp ne i64 %for.loop.idx.next, 186448
  br i1 %exitcond17, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop
  br label %for.loop4

for.loop4:                                        ; preds = %for.loop4, %copy.split
  %for.loop.idx515 = phi i64 [ 0, %copy.split ], [ %for.loop.idx5.next, %for.loop4 ]
  %dst.addr79 = getelementptr %struct.Known_Points_SoA, %struct.Known_Points_SoA* %0, i32 0, i32 1, i64 %for.loop.idx515
  %src.addr810 = getelementptr %struct.Known_Points_SoA, %struct.Known_Points_SoA* %1, i32 0, i32 1, i64 %for.loop.idx515
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %dst.addr79, i8* align 1 %src.addr810, i64 1, i1 false)
  %for.loop.idx5.next = add nuw nsw i64 %for.loop.idx515, 1
  %exitcond = icmp ne i64 %for.loop.idx5.next, 4336
  br i1 %exitcond, label %for.loop4, label %ret

ret:                                              ; preds = %for.loop4, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_out(double*, double* noalias readonly align 512, %struct.BestPoint_SoA*, %struct.BestPoint_SoA* noalias readonly align 512, %struct.Known_Points_SoA*, %struct.Known_Points_SoA* noalias readonly) unnamed_addr #4 {
entry:
  call fastcc void @onebyonecpy_hls.p0f64(double* %0, double* align 512 %1)
  call fastcc void @onebyonecpy_hls.p0struct.BestPoint_SoA(%struct.BestPoint_SoA* %2, %struct.BestPoint_SoA* align 512 %3)
  call fastcc void @onebyonecpy_hls.p0struct.Known_Points_SoA(%struct.Known_Points_SoA* %4, %struct.Known_Points_SoA* %5)
  ret void
}

declare void @free(i8*) local_unnamed_addr

declare i8 @apatb_classifyinstance_hw(double*, i8, %struct.BestPoint_SoA*, i32, %struct.Known_Points_SoA*, i32, i32)

define i8 @classifyinstance_hw_stub_wrapper(double*, i8, %struct.BestPoint_SoA*, i32, %struct.Known_Points_SoA*, i32, i32) #5 {
entry:
  call void @copy_out(double* null, double* %0, %struct.BestPoint_SoA* null, %struct.BestPoint_SoA* %2, %struct.Known_Points_SoA* null, %struct.Known_Points_SoA* %4)
  %7 = call i8 @classifyinstance_hw_stub(double* %0, i8 %1, %struct.BestPoint_SoA* %2, i32 %3, %struct.Known_Points_SoA* %4, i32 %5, i32 %6)
  call void @copy_in(double* null, double* %0, %struct.BestPoint_SoA* null, %struct.BestPoint_SoA* %2, %struct.Known_Points_SoA* null, %struct.Known_Points_SoA* %4)
  ret i8 %7
}

declare i8 @classifyinstance_hw_stub(double*, i8, %struct.BestPoint_SoA*, i32, %struct.Known_Points_SoA*, i32, i32)

attributes #0 = { noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { argmemonly noinline "fpga.wrapper.func"="copyout" }
attributes #5 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
