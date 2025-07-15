#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan Window", nullptr, nullptr);

	VkInstance instance;
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	vkCreateInstance(&createInfo, nullptr, &instance);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	vkDestroyInstance(instance, nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();

}