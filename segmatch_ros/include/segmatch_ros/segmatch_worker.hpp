#ifndef SEGMATCH_ROS_SEGMATCH_WORKER_HPP_
#define SEGMATCH_ROS_SEGMATCH_WORKER_HPP_

#include <laser_slam/common.hpp>
#include <segmatch/segmatch.hpp>

#include "segmatch_ros/common.hpp"

namespace segmatch_ros {

class SegMatchWorker {

 public:
  explicit SegMatchWorker();
  ~SegMatchWorker();
  
  void init(ros::NodeHandle& nh, const SegMatchWorkerParams& params);

  // Process the source cloud and return true if a loop closure was found.
  bool processSourceCloud(const segmatch::PointICloud& source_cloud,
                          const laser_slam::Pose& latest_pose,
                          laser_slam::RelativePose* loop_closure = NULL);

  void update(const laser_slam::Trajectory& trajectory);

 private:

  void loadTargetCloud();

  void publish() const;
  void publishTargetRepresentation() const;
  void publishSourceRepresentation() const;
  void publishMatches() const;
  void publishSegmentationPositions() const;
  void publishLoopClosures() const;
  void publishTargetSegmentsCentroids() const;
  void publishSourceSegmentsCentroids() const;

  // Parameters.
  SegMatchWorkerParams params_;

  // Publishers.
  ros::Publisher source_representation_pub_;
  ros::Publisher target_representation_pub_;
  ros::Publisher matches_pub_;
  ros::Publisher loop_closures_pub_;
  ros::Publisher segmentation_positions_pub_;
  ros::Publisher target_segments_centroids_pub_;
  ros::Publisher source_segments_centroids_pub_;

  // SegMatch object.
  segmatch::SegMatch segmatch_;

  bool target_cloud_loaded_ = false;

  laser_slam::Pose last_segmented_pose_;
  bool last_segmented_pose_set_ = false;

  bool first_localization_occured = false;

  // Publishing parameters.
  static constexpr float kLineScaleSegmentMatches = 0.3;
  static constexpr float kLineScaleLoopClosures = 3.0;

  static constexpr unsigned int kPublisherQueueSize = 50u;
}; // LaserMapper

} // namespace segmatch_ros

#endif /* SEGMATCH_ROS_SEGMATCH_WORKER_HPP_ */
