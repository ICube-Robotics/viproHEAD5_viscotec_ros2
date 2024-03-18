// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef VIPROHEAD_VISCOTEC_ROS2__VISIBILITY_CONTROL_H_
#define VIPROHEAD_VISCOTEC_ROS2__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define VIPROHEAD_VISCOTEC_ROS2_EXPORT __attribute__((dllexport))
#define VIPROHEAD_VISCOTEC_ROS2_IMPORT __attribute__((dllimport))
#else
#define VIPROHEAD_VISCOTEC_ROS2_EXPORT __declspec(dllexport)
#define VIPROHEAD_VISCOTEC_ROS2_IMPORT __declspec(dllimport)
#endif
#ifdef VIPROHEAD_VISCOTEC_ROS2_BUILDING_DLL
#define VIPROHEAD_VISCOTEC_ROS2_PUBLIC VIPROHEAD_VISCOTEC_ROS2_EXPORT
#else
#define VIPROHEAD_VISCOTEC_ROS2_PUBLIC VIPROHEAD_VISCOTEC_ROS2_IMPORT
#endif
#define VIPROHEAD_VISCOTEC_ROS2_PUBLIC_TYPE VIPROHEAD_VISCOTEC_ROS2_PUBLIC
#define VIPROHEAD_VISCOTEC_ROS2_LOCAL
#else
#define VIPROHEAD_VISCOTEC_ROS2_EXPORT __attribute__((visibility("default")))
#define VIPROHEAD_VISCOTEC_ROS2_IMPORT
#if __GNUC__ >= 4
#define VIPROHEAD_VISCOTEC_ROS2_PUBLIC __attribute__((visibility("default")))
#define VIPROHEAD_VISCOTEC_ROS2_LOCAL __attribute__((visibility("hidden")))
#else
#define VIPROHEAD_VISCOTEC_ROS2_PUBLIC
#define VIPROHEAD_VISCOTEC_ROS2_LOCAL
#endif
#define VIPROHEAD_VISCOTEC_ROS2_PUBLIC_TYPE
#endif

#endif  // VIPROHEAD_VISCOTEC_ROS2__VISIBILITY_CONTROL_H_