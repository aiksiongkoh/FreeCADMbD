# Class Hierarchies

```text
std::enable_shared_from_this<ASMTItem>
`- ASMTItem
   |- ASMTAnimationParameters
   |- ASMTConstantGravity
   |- ASMTExtrusion
   |- ASMTItemIJ
   |  |- ASMTConstraintSet
   |  |  |- ASMTContact
   |  |  |  |- ASMTConeConeContact
   |  |  |  |- ASMTCylConeContact
   |  |  |  `- ASMTCylCylContact
   |  |  |- ASMTJoint
   |  |  |  |- ASMTAngleJoint
   |  |  |  |- ASMTAtPointJoint
   |  |  |  |  |- ASMTConstantVelocityJoint
   |  |  |  |  |- ASMTFixedJoint
   |  |  |  |  |- ASMTRevoluteJoint
   |  |  |  |  |- ASMTSphericalJoint
   |  |  |  |  `- ASMTUniversalJoint
   |  |  |  |- ASMTCompoundJoint
   |  |  |  |  |- ASMTCylSphJoint
   |  |  |  |  |- ASMTRevCylJoint
   |  |  |  |  |- ASMTRevRevJoint
   |  |  |  |  `- ASMTSphSphJoint
   |  |  |  |- ASMTGearJoint
   |  |  |  |- ASMTInLineJoint
   |  |  |  |  |- ASMTCylindricalJoint
   |  |  |  |  |- ASMTPointInLineJoint
   |  |  |  |  `- ASMTTranslationalJoint
   |  |  |  |- ASMTInPlaneJoint
   |  |  |  |  |- ASMTLineInPlaneJoint
   |  |  |  |  |- ASMTPlanarJoint
   |  |  |  |  `- ASMTPointInPlaneJoint
   |  |  |  |- ASMTNoRotationJoint
   |  |  |  |- ASMTParallelAxesJoint
   |  |  |  |- ASMTPerpendicularJoint
   |  |  |  |- ASMTRackPinionJoint
   |  |  |  `- ASMTScrewJoint
   |  |  |- ASMTLimit
   |  |  |  |- ASMTRotationLimit
   |  |  |  `- ASMTTranslationLimit
   |  |  `- ASMTMotion
   |  |     |- ASMTAllowRotation
   |  |     |- ASMTGeneralMotion
   |  |     |- ASMTRotationalMotion
   |  |     `- ASMTTranslationalMotion
   |  |- ASMTForceTorque
   |  |  |- ASMTForceTorqueGeneral
   |  |  `- ASMTForceTorqueInLine
   |  `- ASMTKinematicIJ
   |- ASMTSimulationParameters
   `- ASMTSpatialItem
      |- ASMTMarker
      |  `- ASMTMarkerTemp
      |- ASMTPrincipalMassMarker
      |- ASMTRefItem
      |  |- ASMTRefCurve
      |  |- ASMTRefPoint
      |  `- ASMTRefSurface
      `- ASMTSpatialContainer
         |- ASMTAssembly
         `- ASMTPart

std::enable_shared_from_this<Item>
`- Item
   |- CartesianFrame
   |  |- EndFrame
   |  |  |- EndFrameccq
   |  |  |- EndFramet
   |  |  `- EndFrameq
   |  |     |- EndFrameqccq
   |  |     `- EndFrameqt
   |  |        `- EndFrameqt2
   |  |- MarkerFrame
   |  |  `- MarkerFrameq
   |  `- SpatialContainerFrame
   |     |- AssemblyFrame
   |     `- PartFrame
   |- Constraint
   |  |- AbsConstraint
   |  |- ConstraintIeJe
   |  |  |- AtPointConstraintIeJe
   |  |  |  |- AtPointConstraintIeJeq
   |  |  |  |  `- AtPointConstraintIetJeq
   |  |  |  `- AtPointConstraintIeqJe
   |  |  |     `- AtPointConstraintIeqJeq
   |  |  |        `- AtPointConstraintIeqtJeq
   |  |  |- DirectionCosineConstraintIeJe
   |  |  |  |- DirectionCosineConstraintIeJeq
   |  |  |  |  `- DirectionCosineConstraintIetJeq
   |  |  |  |     `- AllowZRotationConstraintIetJeq
   |  |  |  `- DirectionCosineConstraintIeqJe
   |  |  |     `- DirectionCosineConstraintIeqJeq
   |  |  |        `- DirectionCosineConstraintIeqtJeq
   |  |  |           `- AllowZRotationConstraintIeqtJeq
   |  |  |- TranslationConstraintIeJe
   |  |  |  |- TranslationConstraintIeJeq
   |  |  |  |  `- TranslationConstraintIetJeq
   |  |  |  `- TranslationConstraintIeqJe
   |  |  |     `- TranslationConstraintIeqJeq
   |  |  |        `- TranslationConstraintIeqtJeq
   |  |  |- AngleZConstraintIeJe
   |  |  |  |- AngleZConstraintIeJeq
   |  |  |  `- AngleZConstraintIeqJe
   |  |  |     `- AngleZConstraintIeqJeq
   |  |  |- ConstVelConstraintIeJe
   |  |  |  `- ConstVelConstraintIeqJe
   |  |  |     `- ConstVelConstraintIeqJeq
   |  |  |- DistanceConstraintIeJe
   |  |  |  `- DistanceConstraintIeqJe
   |  |  |     `- DistanceConstraintIeqJeq
   |  |  |        `- DistanceConstraintIeqtJeq
   |  |  |- DistancexyConstraintIeJe
   |  |  |  `- DistancexyConstraintIeqJe
   |  |  |     `- DistancexyConstraintIeqJeq
   |  |  |- GearConstraintIeJe
   |  |  |  `- GearConstraintIeqJe
   |  |  |     `- GearConstraintIeqJeq
   |  |  |- RackPinConstraintIeJe
   |  |  |  `- RackPinConstraintIeqJe
   |  |  |     `- RackPinConstraintIeqJeq
   |  |  `- ScrewConstraintIeJe
   |  |     `- ScrewConstraintIeqJe
   |  |        `- ScrewConstraintIeqJeq
   |  |- EulerConstraint
   |  `- RedundantConstraint
   |- ConstraintSet
   |  |- JointIJ
   |  |  |- AngleJoint
   |  |  |- AtPointJoint
   |  |  |  |- ConstantVelocityJoint
   |  |  |  |- FixedJoint
   |  |  |  |- RevoluteJoint
   |  |  |  |- SphericalJoint
   |  |  |  `- UniversalJoint
   |  |  |- CompoundJoint
   |  |  |  |- CylSphJoint
   |  |  |  |- RevCylJoint
   |  |  |  |- RevRevJoint
   |  |  |  `- SphSphJoint
   |  |  |- GearJoint
   |  |  |- InLineJoint
   |  |  |  |- CylindricalJoint
   |  |  |  |- PointInLineJoint
   |  |  |  `- TranslationalJoint
   |  |  |- InPlaneJoint
   |  |  |  |- LineInPlaneJoint
   |  |  |  |- PlanarJoint
   |  |  |  `- PointInPlaneJoint
   |  |  |- NoRotationJoint
   |  |  |- ParallelAxesJoint
   |  |  |- PerpendicularJoint
   |  |  |- RackPinJoint
   |  |  `- ScrewJoint
   |  |- LimitIJ
   |  |  |- RotationLimitIJ
   |  |  `- TranslationLimitIJ
   |  `- PrescribedMotion
   |     |- AllowZRotation
   |     |- FullMotion
   |     |- Orientation
   |     |- Translation
   |     |- ZRotation
   |     `- ZTranslation
   |- ForceTorqueItem
   |  |- ConstantGravity
   |  |- ForceTorqueFunction
   |  `- ForceTorqueIJ
   |     |- ForceTorqueGeneral
   |     `- ForceTorqueInLine
   |- Kinematic
   |  |- KinematicIeJe
   |  |  |- KinematicCompiIeJe
   |  |  |  |- DispCompiIeJeIe
   |  |  |  |- DispCompiIeJeKe
   |  |  |  `- DispCompiIeJeO
   |  |  |- AngleZIeJe
   |  |  |  |- AngleZIeJeq
   |  |  |  `- AngleZIeqJe
   |  |  |     `- AngleZIeqJeq
   |  |  |- DAngleXIeJe
   |  |  |  `- DAngleXIeqJe
   |  |  |     `- DAngleXIeqJeq
   |  |  |- DAngleYIeJe
   |  |  |  `- DAngleYIeqJe
   |  |  |- DirectionCosineIeJe
   |  |  |  |- DirectionCosineIeJeq
   |  |  |  |  `- DirectionCosineIetJeq
   |  |  |  `- DirectionCosineIeqJe
   |  |  |     `- DirectionCosineIeqJeq
   |  |  |        `- DirectionCosineIeqtJeq
   |  |  |- DistIeJe
   |  |  |  |- DistIeqJe
   |  |  |  |  `- DistIeqJeq
   |  |  |  |     `- DistIeqtJeq
   |  |  |  `- DistIeJeq
   |  |  |     `- DistIetJeq
   |  |  |- DistxyIeJe
   |  |  |  `- DistxyIeqJe
   |  |  |     `- DistxyIeqJeq
   |  |  |        `- DistxyIeqtJeq
   |  |  |- KinematicDotIeJe
   |  |  |  |- OmeCompIeJeKe
   |  |  |  |  |- OmeCompIeJeqKe
   |  |  |  |  `- OmeCompIeqJeKeq
   |  |  |  |     `- OmeCompIeqJeqKeq
   |  |  |  |- OmeCompIeJeO
   |  |  |  |  `- OmeCompIeqJeO
   |  |  |  |     `- OmeCompIeqJeqO
   |  |  |  `- VelRadIeJe
   |  |  |     |- VelRadIeJeq
   |  |  |     |  `- VelRadIetJeq
   |  |  |     `- VelRadIeqJe
   |  |  |        `- VelRadIeqJeq
   |  |  |           `- VelRadIeqtJeq
   |  |  `- OrbitAngleZIeJe
   |  |     `- OrbitAngleZIeqJe
   |  |        `- OrbitAngleZIeqJeq
   |  `- KinematicVectorIeJe
   |     |- DispIeJeKe
   |     |  |- DispIeJeKeq
   |     |  |- DispIeJeqKe
   |     |  |  |- DispIeJeqKeq
   |     |  |  `- DispIetJeqKet
   |     |  `- DispIeqJeKe
   |     |     |- DispIeqJeKeq
   |     |     `- DispIeqJeqKe
   |     |        `- DispIeqJeqKeq
   |     |           `- DispIeqtJeqKeqt
   |     `- DispIeJeO
   |        |- DispIeJeqO
   |        |  `- DispIetJeqO
   |        `- DispIeqJeO
   |           `- DispIeqJeqO
   |              `- DispIeqtJeqO
   |- Part
   |- StateData
   |  |- ForceTorqueData
   |  `- PosVelAccData
   `- System

std::enable_shared_from_this<MbDMath>
`- MbDMath
   |- Numeric
   |  |- DifferenceOperator
   |  |  |- Extrapolator
   |  |  |  `- Interpolator
   |  |  `- LinearMultiStepMethod
   |  |     |- BackwardDifference
   |  |     |  `- StartingBDF
   |  |     `- StableBackwardDifference
   |  |        `- StableStartingBDF
   |  |- Solver
   |  |  |- DifferentialAlgebraicEquationSolver
   |  |  |- Integrator
   |  |  |  |- BasicIntegrator
   |  |  |  |  |- BasicDAEIntegrator
   |  |  |  |  |  |- NormalBasicDAEIntegrator
   |  |  |  |  |  `- StartingBasicDAEIntegrator
   |  |  |  |  `- BasicQuasiIntegrator
   |  |  |  `- IntegratorInterface
   |  |  |     |- DAEIntegrator
   |  |  |     |  `- DynIntegrator
   |  |  |     `- QuasiIntegrator
   |  |  |        |- ICKineIntegrator
   |  |  |        |- KineIntegrator
   |  |  |        `- QuasiStaticIntegrator
   |  |  |- MatrixSolver
   |  |  |  |- EigenDecomposition
   |  |  |  |  `- MomentOfInertiaSolver
   |  |  |  |- MatrixDecomposition
   |  |  |  |  `- MatrixLDU
   |  |  |  |     |- LDUFullMat
   |  |  |  |     |  `- LDUFullMatParPv
   |  |  |  |     |     `- LDUFullMatParPvRobust
   |  |  |  |     `- LDUSpMat
   |  |  |  |        `- LDUSpMatParPv
   |  |  |  |           |- LDUSpMatParPvMarko
   |  |  |  |           `- LDUSpMatParPvPrecise
   |  |  |  `- MatrixGaussElimination
   |  |  |     |- GEFullMat
   |  |  |     |  |- GEFullMatFullPv
   |  |  |     |  `- GEFullMatParPv
   |  |  |     `- GESpMat
   |  |  |        |- GESpMatFullPv
   |  |  |        |  `- GESpMatFullPvPosIC
   |  |  |        `- GESpMatParPv
   |  |  |           |- GESpMatParPvMarko
   |  |  |           |  `- GESpMatParPvMarkoFast
   |  |  |           `- GESpMatParPvPrecise
   |  |  |- NewtonRaphson
   |  |  |  |- ScalarNewtonRaphson
   |  |  |  `- VectorNewtonRaphson
   |  |  |     |- DAECorrector
   |  |  |     `- SystemNewtonRaphson
   |  |  |        |- AccNewtonRaphson
   |  |  |        |  |- AccICNewtonRaphson
   |  |  |        |  |  `- AccICKineNewtonRaphson
   |  |  |        |  `- AccKineNewtonRaphson
   |  |  |        `- PosNewtonRaphson
   |  |  |           |- AnyPosICNewtonRaphson
   |  |  |           |  |- PosICDragLimitNewtonRaphson
   |  |  |           |  |- PosICDragNewtonRaphson
   |  |  |           |  |- PosICKineNewtonRaphson
   |  |  |           |  `- PosICNewtonRaphson
   |  |  |           `- PosKineNewtonRaphson
   |  |  |- SystemSolver
   |  |  `- VelSolver
   |  |     |- VelICSolver
   |  |     |  `- VelICKineSolver
   |  |     `- VelKineSolver
   |  `- Units
   `- Symbolic
      |- Function
      |  |- FunctionWithManyArgs
      |  |  |- Arguments
      |  |  |  |- Functions
      |  |  |  `- Transitions
      |  |  |- Product
      |  |  `- Sum
      |  |- FunctionX
      |  |  |- Abs
      |  |  |- ArcSine
      |  |  |- ArcTan
      |  |  |- Cosine
      |  |  |- Exponential
      |  |  |- ExpressionX
      |  |  |  |- CADSymbolicFunction
      |  |  |  |  |- ASMTSymbolicFunction
      |  |  |  |  |  |- ASMTSymbolicFunctionIJ
      |  |  |  |  |  |  |- ASMTAngleIJ
      |  |  |  |  |  |  |  |- ASMTAngleIJz
      |  |  |  |  |  |  |  |- ASMTdAngleIJx
      |  |  |  |  |  |  |  `- ASMTdAngleIJy
      |  |  |  |  |  |  |- ASMTForceIJ
      |  |  |  |  |  |  |- ASMTOmegaIJ
      |  |  |  |  |  |  |- ASMTrIJ
      |  |  |  |  |  |  |- ASMTSymbolicFunctionIJKi
      |  |  |  |  |  |  |  |- ASMTForceIJKi
      |  |  |  |  |  |  |  |- ASMTOmegaIJKi
      |  |  |  |  |  |  |  |- ASMTrIJKi
      |  |  |  |  |  |  |  |- ASMTTorqueIJKi
      |  |  |  |  |  |  |  `- ASMTvIJKi
      |  |  |  |  |  |  |- ASMTTorqueIJ
      |  |  |  |  |  |  |- ASMTvIJ
      |  |  |  |  |  |  `- ASMTvrIJ
      |  |  |  |  |  `- ASMTTime
      |  |  |  |  `- MbDSymbolicFunction
      |  |  |  `- Integral
      |  |  |- FunctionXcParameter
      |  |  |  |- FunctionFromData
      |  |  |  |  `- AnyGeneralSpline
      |  |  |  |     |- DifferentiatedGeneralSpline
      |  |  |  |     `- GeneralSpline
      |  |  |  |- PiecewiseFunction
      |  |  |  |  |- RampStepFunction
      |  |  |  |  `- StepFunction
      |  |  |  `- Polynomial
      |  |  |- Ln
      |  |  |- Log10
      |  |  |- LogN
      |  |  |- Negative
      |  |  |- Reciprocal
      |  |  `- Sine
      |  `- FunctionXY
      |     |- ArcTan2
      |     `- Power
      |- UserFunction
      |  `- BasicUserFunction
      `- Variable
         |- Constant
         `- IndependentVariable
            `- SymTime

std::enable_shared_from_this<MBDynItem>
`- MBDynItem
   |- MBDynBlock
   |  |- MBDynControlData
   |  |  `- MBDynOutputMeter
   |  |- MBDynData
   |  `- MBDynInitialValue
   |- MBDynElement
   |  |- MBDynBody
   |  |- MBDynDrive
   |  |  |- MBDynDriveCosine
   |  |  |- MBDynDriveElement
   |  |  |- MBDynDriveMeter
   |  |  |- MBDynDriveRamp
   |  |  |- MBDynDriveSine
   |  |  `- MBDynDriveString
   |  |- MBDynForce
   |  |  `- MBDynAbsoluteForce
   |  |- MBDynGenel
   |  |  `- MBDynClampGenel
   |  |- MBDynGravity
   |  |- MBDynJoint
   |  |  |- MBDynAxialRotationJoint
   |  |  |- MBDynClampJoint
   |  |  |- MBDynDriveHingeJoint
   |  |  |- MBDynInLineJoint
   |  |  |- MBDynInPlaneJoint
   |  |  |- MBDynPrismaticJoint
   |  |  |- MBDynRevoluteHingeJoint
   |  |  |- MBDynRevolutePinJoint
   |  |  |- MBDynRodJoint
   |  |  |- MBDynSphericalHingeJoint
   |  |  `- MBDynTotalJoint
   |  `- MBDynPlugin
   |     `- MBDynNodePlugin
   |- MBDynMarker
   |- MBDynNode
   |  `- MBDynStructural
   |     |- MBDynStructuralDummy
   |     |- MBDynStructuralDynamic
   |     `- MBDynStructuralStatic
   |- MBDynReference
   |- MBDynScalarFunction
   `- MBDynSystem

std::enable_shared_from_this<SymbolicParser>
`- SymbolicParser
   `- FunctionParser
      |- ForceFunctionParser
      `- MotionFunctionParser

std::map<size_t, T>
`- SparseVector<T>
   |- SparseColumn<T>
   `- SparseRow<T>

std::vector<T>
`- Array
   |- DiagonalMatrix
   |- FullVector<T>
   |  |- FullColumn<T>
   |  |  `- EulerArray<T>
   |  |     |- EulerAngles
   |  |     |- EulerAnglesDDot
   |  |     |- EulerAnglesDot
   |  |     |- EulerAngleszxz
   |  |     |- EulerAngleszxzDDot
   |  |     |- EulerAngleszxzDot
   |  |     |- EulerParameters
   |  |     |- EulerParametersDDot
   |  |     `- EulerParametersDot
   |  `- FullRow<T>
   `- RowTypeMatrix<T>
      |- FullMatrix
      `- SparseMatrix
```


CADMbDFEM
CMFNode(sup subs extCADItem)
    CADItem()
        CADAssembly
        CADPart
    MbDItem(extMbDItem cadItem)
        MbDAssembly
        MbDPart
        MbDMarker
        MbDIJ(mkrI mkrJ)
            MbDJoint
            MbDForceTorque
    FEMItem(extFEMItem cadItem mbdItem)
        FEMAssembly
        FEMPart
        FEMMeshElement
        FEMMeshNode
        FEMCLoad
        FEMDLoad
        FEMConstraint


App::Part(Group InList OutList Placement)
    CADItem()			not needed. Same as App::Part
        CADAssembly		not needed. Same as App::Part
        CADPart			not needed. Same as App::Part
    MbDItem(extMbDItem cadItem)		cadItem has App::Part
        MbDAssembly
        MbDPart
        MbDMarker
        MbDIJ(mkrI mkrJ)
            MbDJoint
            MbDForceTorque
    FEMItem(extFEMItem cadItem mbdItem) cadItem has App::Part
        FEMAssembly
        FEMPart
        FEMMeshElement
        FEMMeshNode
        FEMCLoad
        FEMDLoad
        FEMConstraint
