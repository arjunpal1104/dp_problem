import java.util.*;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

public class CandidateCode {

  static final Pattern pattern = Pattern.compile(
    "(\\w{2,}+\\.( ){1,})|(, \\w+)"
  );
  static final SimpleRatio fuzzy = new SimpleRatio();

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    Map<String, List<String>> map = new HashMap<String, List<String>>() {
      {
        put(
          "nameA",
          new ArrayList<String>(
            Arrays.asList(
              pattern
                .matcher(sc.nextLine())
                .replaceAll("")
                .toLowerCase()
                .replaceAll("ee", "i")
                .replaceAll("aa", "a")
                .split(" ")
            )
          )
        );
        put(
          "nameB",
          new ArrayList<String>(
            Arrays.asList(
              pattern
                .matcher(sc.nextLine())
                .replaceAll("")
                .toLowerCase()
                .replaceAll("ee", "i")
                .replaceAll("aa", "a")
                .split(" ")
            )
          )
        );
      }
    };

    removeTitle(map);
    if (matchSubset(map)) {
      System.out.print("Match");
    } else if (
      fuzzy.apply(
        String.join("", map.get("nameA")),
        String.join("", map.get("nameB"))
      ) >
      69
    ) {
      System.out.print("Match");
    } else if (matchInitials(map)) {
      System.out.print("Match");
    } else {
      System.out.print("No Match");
    }
  }

  static void removeTitle(Map<String, List<String>> map) {
    for (int i = 0; i < map.get("nameA").size(); i++) {
      if (
        map.get("nameA").get(i).chars().anyMatch(c -> !Character.isLetter(c))
      ) {
        map.get("nameA").remove(i);
      }
    }
    for (int i = 0; i < map.get("nameB").size(); i++) {
      if (
        map.get("nameB").get(i).chars().anyMatch(c -> !Character.isLetter(c))
      ) {
        map.get("nameB").remove(i);
      }
    }
  }

  static boolean matchSubset(Map<String, List<String>> map) {
    boolean b = false;
    if (map.get("nameA").containsAll(map.get("nameB"))) {
      b = true;
    } else if (map.get("nameB").containsAll(map.get("nameA"))) {
      b = true;
    }
    return b;
  }

  static boolean matchInitials(Map<String, List<String>> map) {
    Collections.sort(map.get("nameA"));
    Collections.sort(map.get("nameB"));
    if (map.get("nameA").size() == map.get("nameB").size()) {
      for (int i = 0; i < map.get("nameA").size(); i++) {
        if (
          map.get("nameA").get(i).length() == 1 &&
          map.get("nameB").get(i).length() > 1
        ) {
          if (
            map.get("nameA").get(i).charAt(0) !=
            map.get("nameB").get(i).charAt(0)
          ) {
            return false;
          }
        } else if (
          map.get("nameA").get(i).length() > 1 &&
          map.get("nameB").get(i).length() == 1
        ) {
          if (
            map.get("nameA").get(i).charAt(0) !=
            map.get("nameB").get(i).charAt(0)
          ) {
            return false;
          }
        } else if (!map.get("nameA").get(i).equals(map.get("nameB").get(i))) {
          return false;
        }
      }
      return true;
    }
    return false;
  }
}

class SimpleRatio implements Ratio {

  @Override
  public int apply(String s1, String s2) {
    return (int) Math.round(100 * DiffUtils.getRatio(s1, s2));
  }

  @Override
  public int apply(String s1, String s2, ToStringFunction<String> sp) {
    return apply(sp.apply(s1), sp.apply(s2));
  }
}

interface ToStringFunction<T> {
  String apply(T item);
  ToStringFunction<String> NO_PROCESS = new ToStringFunction<String>() {
    @Override
    public String apply(String item) {
      return item;
    }
  };
}

interface Ratio extends Applicable {
  int apply(String s1, String s2);
  int apply(String s1, String s2, ToStringFunction<String> sp);
}

interface Applicable {
  int apply(String s1, String s2);
}

class DiffUtils {

  public static int levEditDistance(String s1, String s2, int xcost) {
    int i;
    int half;

    char[] c1 = s1.toCharArray();
    char[] c2 = s2.toCharArray();

    int str1 = 0;
    int str2 = 0;

    int len1 = s1.length();
    int len2 = s2.length();

    /* strip common prefix */
    while (len1 > 0 && len2 > 0 && c1[str1] == c2[str2]) {
      len1--;
      len2--;
      str1++;
      str2++;
    }

    /* strip common suffix */
    while (len1 > 0 && len2 > 0 && c1[str1 + len1 - 1] == c2[str2 + len2 - 1]) {
      len1--;
      len2--;
    }

    /* catch trivial cases */
    if (len1 == 0) return len2;
    if (len2 == 0) return len1;

    /* make the inner cycle (i.e. str2) the longer one */
    if (len1 > len2) {
      int nx = len1;
      int temp = str1;

      len1 = len2;
      len2 = nx;

      str1 = str2;
      str2 = temp;

      char[] t = c2;
      c2 = c1;
      c1 = t;
    }

    /* check len1 == 1 separately */
    if (len1 == 1) {
      if (xcost != 0) {
        return len2 + 1 - 2 * memchr(c2, str2, c1[str1], len2);
      } else {
        return len2 - memchr(c2, str2, c1[str1], len2);
      }
    }

    len1++;
    len2++;
    half = len1 >> 1;

    int[] row = new int[len2];
    int end = len2 - 1;

    for (i = 0; i < len2 - (xcost != 0 ? 0 : half); i++) row[i] = i;

    /* go through the matrix and compute the costs.  yes, this is an extremely
     * obfuscated version, but also extremely memory-conservative and relatively
     * fast.  */

    if (xcost != 0) {
      for (i = 1; i < len1; i++) {
        int p = 1;

        char ch1 = c1[str1 + i - 1];
        int c2p = str2;

        int D = i;
        int x = i;

        while (p <= end) {
          if (ch1 == c2[c2p++]) {
            x = --D;
          } else {
            x++;
          }
          D = row[p];
          D++;

          if (x > D) x = D;
          row[p++] = x;
        }
      }
    } else {
      /* in this case we don't have to scan two corner triangles (of size len1/2)
       * in the matrix because no best path can go throught them. note this
       * breaks when len1 == len2 == 2 so the memchr() special case above is
       * necessary */

      row[0] = len1 - half - 1;
      for (i = 1; i < len1; i++) {
        int p;

        char ch1 = c1[str1 + i - 1];
        int c2p;

        int D, x;

        /* skip the upper triangle */
        if (i >= len1 - half) {
          int offset = i - (len1 - half);
          int c3;

          c2p = str2 + offset;
          p = offset;
          c3 = row[p++] + ((ch1 != c2[c2p++]) ? 1 : 0);
          x = row[p];
          x++;
          D = x;
          if (x > c3) {
            x = c3;
          }
          row[p++] = x;
        } else {
          p = 1;
          c2p = str2;
          D = x = i;
        }
        /* skip the lower triangle */
        if (i <= half + 1) end = len2 + i - half - 2;
        /* main */
        while (p <= end) {
          int c3 = --D + ((ch1 != c2[c2p++]) ? 1 : 0);
          x++;
          if (x > c3) {
            x = c3;
          }
          D = row[p];
          D++;
          if (x > D) x = D;
          row[p++] = x;
        }

        /* lower triangle sentinel */
        if (i <= half) {
          int c3 = --D + ((ch1 != c2[c2p]) ? 1 : 0);
          x++;
          if (x > c3) {
            x = c3;
          }
          row[p] = x;
        }
      }
    }

    i = row[end];

    return i;
  }

  private static int memchr(char[] haystack, int offset, char needle, int num) {
    if (num != 0) {
      int p = 0;
      do {
        if (haystack[offset + p] == needle) return 1;
        p++;
      } while (--num != 0);
    }
    return 0;
  }

  public static double getRatio(String s1, String s2) {
    int len1 = s1.length();
    int len2 = s2.length();
    int lensum = len1 + len2;
    int editDistance = levEditDistance(s1, s2, 1);
    return (lensum - editDistance) / (double) lensum;
  }
}