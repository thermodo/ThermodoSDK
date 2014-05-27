require 'xcodeproj'

BUILD_PHASE_FRAMEWORKS_SUBFOLDER = "10"
BUILD_PHASE_NAME = "Copy Thermodo SDK"
FRAMEWORK_NAME = "ThermodoSDKMac.framework"
FRAMEWORK_PATH = "Pods/ThermodoSDK/Frameworks/#{FRAMEWORK_NAME}"

Dir.glob("../../*.xcodeproj").each do |project_file|
  project = Xcodeproj::Project.open(project_file)
  target = project.targets.first
  # Find OS X target
  if not target.nil? and target.platform_name == :osx
    # Check if valid copy files build phase exists
    build_phase = target.copy_files_build_phases.find{ |phase| phase.dst_subfolder_spec == BUILD_PHASE_FRAMEWORKS_SUBFOLDER and phase.display_name == BUILD_PHASE_NAME }
    if build_phase.nil? or build_phase.files.find{ |file| file.display_name == FRAMEWORK_NAME }.nil?
      # The framework has been removed from the existing build phase,
      # remove it before we add a new build phase
      if not build_phase.nil?
        build_phase.remove_from_project
      end
      # Check if there is already a reference to the file
      file_ref = project.files.find{ |file| file.display_name == FRAMEWORK_NAME }
      if file_ref.nil?
        group = project.groups.find{ |group| group.name == "Frameworks" }
        file_ref = project.new_file(FRAMEWORK_PATH)
        file_ref.move(group)
      end
      phase = target.new_copy_files_build_phase(BUILD_PHASE_NAME)
      phase.dst_subfolder_spec = BUILD_PHASE_FRAMEWORKS_SUBFOLDER
      phase.add_file_reference(file_ref, true)
      project.save()
    end
  end
end
