#!/usr/bin/env python3

import rospy
from my_awesome_code.srv import WordCount,WordCountResponse

def count_Words(request):
    return WordCountResponse(len(request.Words.split()))
rospy.init_node('service_server')
service=rospy.Service('word_count',WordCount,count_Words)
rospy.spin()


