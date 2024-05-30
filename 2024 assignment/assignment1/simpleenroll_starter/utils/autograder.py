'''
Hey friend! Glad you're curious about this, but please don't touch this file :>)
'''

from csv_utils import *
import os

def main():
  # 假设你的工作目录是 /mnt/e/c++documents/CS106L/assignment1/simpleenroll_starter/
  base_path = "/mnt/e/c++documents/CS106L/assignment1/simpleenroll_starter/"
  utils_path = os.path.join(base_path, "utils")
  student_output_path = os.path.join(base_path, "student_output")

  # 更新路径以适应你的文件系统
  binary_to_csv(os.path.join(utils_path, "courses_not_offered.bin"), os.path.join(utils_path, "courses_not_offered.csv"))
  binary_to_csv(os.path.join(utils_path, "courses_offered.bin"), os.path.join(utils_path, "courses_offered.csv"))

  # 验证文件
  assert files_are_equal(os.path.join(utils_path, "courses_offered.csv"), os.path.join(student_output_path, "courses_offered.csv")), "write_courses_offered test failed 😞"
  assert files_are_equal(os.path.join(utils_path, "courses_not_offered.csv"), os.path.join(student_output_path, "courses_not_offered.csv")), "write_courses_not_offered test failed 😞"

  # 清理生成的文件
  os.remove(os.path.join(utils_path, "courses_not_offered.csv"))
  os.remove(os.path.join(utils_path, "courses_offered.csv"))

  print("Congratulations, your code passes all the autograder tests! ✅")


main()
